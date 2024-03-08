#include "cub3d.h"
#include <OpenGL/OpenGL.h>
#include <math.h>

float	px,py,pdx,pdy,pa;  // Player Position

void draw_player()
{
	glColor3f(1, 1, 0);
	glPointSize(20);
	glBegin(GL_POINTS);
	glVertex2i(px, py);
	glEnd();

	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2i(px, py);
	glVertex2i(px+pdx*5, py+pdy*5);
	glEnd();
}

int mapX = 8, mapY = 8, mapS = 64;
int	map[] = 
{
	1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,
};

void	drawMap2D()
{
	int	x, y, xo, yo;
	y = -1;
	while (++y < mapY)
	{
		x = -1;
		while (++x < mapX)
		{
			if (map[y*mapX+x] == 1)
				glColor3f(1, 1, 1);
			else
				glColor3f(0, 0, 0);
			xo = x*mapS;
			yo = y*mapS;
			glBegin(GL_QUADS);
			glVertex2i(xo + 1, yo + 1); // Bottom-left corner
			glVertex2i(xo + 1, yo + mapS - 1); // Bottom-right corner
			glVertex2i(xo+mapS - 1,yo + mapS - 1); // Top-right corner
			glVertex2i(xo+mapS - 1, yo + 1); // Top-left corner
			glEnd();
		}
	}
}

float	shortest_distance(float ax, float ay, float bx, float by, float ang)
{
	return (sqrt((bx-ax)*(bx-ax) + (by-ay)*(by-ay)));
}

void	drawRays2D()
{
	int		r, mx, my, mp, dof; // m = map -- dof = depth of field
	float	rx, ry, ra, xo, yo, disT; // r = ray -- disT = shortest distance value comparison
	
	ra = pa - DR*30;
	if (ra < 0)
		ra += 2*PI; // below 0 means its wrong value, so we make it in range of 360 -- 2PI
	else if (ra > 2*PI)
		ra -=+2*PI; // grater than 2*PI (360) means its wrong value, so we make it in range of 360
	r = -1;
	while (++r < 60)
	{
		//================== Check HORIZENTAL Lines ===================//
		// if angle > PI then it means he is looking Down. 
		dof = 0;
		float disH = 1000000, hx=px, hy=py;
		float aTan = -1/tan(ra); // Negative Value of Tan
		if (ra > PI)
		{
			ry = (((int)py>>6)<<6) - 0.0001;
			rx = (py-ry) * aTan + px;
			yo = -64;
			xo = -yo * aTan;
		}
		// if 0 > angle < PI this means he is looking up.
		if (ra < PI)
		{
			ry = (((int)py>>6)<<6) + 64;
			rx = (py-ry) * aTan + px;
			yo = 64;
			xo = -yo * aTan;
		}
		//looking straight LEFT OR RIGHT its impossible to hit a Horizental line
		// Because the compiler will cry about having the comparing of
		// ra == PI, since they are both floats then this means the result
		// may not be accurate, so in this case we can use EPSLION = 0.0001
		// which means that if they are really close to each other then this will
		// be evaluated to true
		if (ra == 0 || (fabs(ra - PI) < EPSILON)) // 
		{
			rx = px;
			ry = py;
			dof = 8;
		}
		while (dof < 8)
		{
			/*
			##########
			#     /  # Here the ray hit a wall and the loop finished
			#    /   # we set Depth of Field = dof to 8
			#   /	 # which will break the loop, meaning we hit a wall
			#  O	 # (**5) the map[mp] controls the color also, if we make it > 0
			########## The color will change
			 second case
			##############
			#			 # 	If we didn't hit a wall
			#			 # then it means that the wall still far away
			#			 # so in this case we need to try again, but how ?
			#     /  	 #
			#    /   	 #
			#   /		 #
			#  O	 	 #
			##############
			so to fix this
			##############
			#		 /   # we add the offsets again to the previous inits
			#		/	 # so in this case we will loop again
			#	   /	 # until we hit a wall and our loop will end
			#     /  	 #  
			#    /   	 # this what makes Ray casting really awesome
			#   /		 # optimized and super fast its accuracy
			#  O	 	 #
			##############
			*/
			mx = (int)(rx)>>6; // >>6 is equal to divide by 64 which is the map dimentions 
			my = (int)(ry)>>6; // so we know which part of map we are in
			mp = my*mapX+mx;
			if (mp > 0 && mp<mapX*mapY && map[mp] == 1) // if map[mp] == 1 hit a Wall, **5
			{
				hx = rx;
				hy = ry;
				disH = shortest_distance(px, py, hx, hy, ra);
				dof = 8;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		//================== Check VERTICAL Lines ===================//
		dof = 0;
		float disV = 1000000, vx=px, vy=py;
		float nTan = -tan(ra); // Normal Value of Tan
		if (ra > PI2 && ra < PI3) // looking LEFT. 
		{
			rx = (((int)px>>6)<<6) - 0.0001;
			ry = (px-rx) * nTan + py;
			xo = -64;
			yo = -xo * nTan;
		}
		if (ra < PI2 || ra > PI3) // looking RIGHT.
		{
			rx = (((int)px>>6)<<6) + 64;
			ry = (px-rx) * nTan + py;
			xo = 64;
			yo = -xo * nTan;
		}
		if (ra == 0 || (fabs(ra - PI) < EPSILON)) // looking straight UP or DOWN
		{
			rx = px;
			ry = py;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx)>>6;
			my = (int)(ry)>>6;
			mp = my*mapX+mx;
			if (mp > 0 && mp<mapX*mapY && map[mp] == 1)
			{
				vx = rx;
				vy = ry;
				disV = shortest_distance(px, py, vx, vy, ra);
				dof = 8;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		if (disV < disH)
		{
			rx = vx;
			ry = vy;
			disT = disV;
			glColor3f(0.9, 0, 0); // Vertical Wall hit color
		}
		else if (disH < disV)
		{
			rx = hx;
			ry = hy;
			disT = disH;
			glColor3f(0.7, 0, 0); // Horizontal Wall hit color
		}
		glLineWidth(3);
		glBegin(GL_LINES);
		glVertex2i(px, py);
		glVertex2i(rx, ry);
		glEnd();
		//================== Draw 3D Scene ===================//
		/*
		mapS = Cube Size
		320 = new screen height
		disT = Ray distance
		so the further away the larger the distance, but
		the shorter the line height will be
		because the line height is denominator so it controls the output basically
		because its 320 so we cap the lineH at that Value
		*/
		float lineH = (mapS*320) / disT; // line height
		if (lineH > 320)
			lineH = 320; // because its 320 so we cap the lineH at that Value
		/*
		But there is an issue here, which is the cubes are not in the center
		so to fix it, we introduce the offset, which can be helpful too
		it will offset it to the center of the screen
		*/
		float lineO = 160 - lineH/2; // line offset
		/*
		Another issue, We get the warp issue, aka the fisheye, which can be fixed
		with cosine, as we need to know the distance between
		player angle and ray angle == ca, then limit it ofc
		*/
		float ca = pa - ra;
		if (ca < 0)
			ca += 2*PI;
		else if (ca > 2*PI)
			ca -= 2*PI;
		disT = disT*cos(ca);
		glLineWidth(8);
		glBegin(GL_LINES);
		glVertex2i(r*8+530, lineO);
		glVertex2i(r*8+530, lineH+lineO);
		glEnd();
		ra += DR;
		if (ra < 0)
			ra += 2*PI;
		else if (ra > 2*PI)
			ra -=+2*PI;
	}
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawMap2D();
	draw_player();
	drawRays2D();
	glutSwapBuffers();
}

void buttons(unsigned char key, int x, int y)
{
	if ( key == 'a')
	{
		pa -= 0.1;
		if (pa < 0)
			pa += 2*PI;
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
	}
	if ( key == 'd')
	{
		pa += 0.1;
		if (pa > 2*PI)
			pa -= 2*PI;
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
	}
	if ( key == 'w')
	{
		px += pdx;
		py += pdy;
	}
	if ( key == 's')
	{
		px -= pdx;
		py -= pdy;
	}
	glutPostRedisplay();
}

void init()
{
	glClearColor(0.3, 0.3, 0.3, 0);
	gluOrtho2D(0, 1024, 512, 0);
	px = 300;			py = 300;
	pdx = cos(pa) * 5;	pdy = sin(pa) * 5;
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1024,512);
	glutCreateWindow("My Own Game");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(buttons);
	glutMainLoop();
}
