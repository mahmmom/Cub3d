#include "cub3d.h"
#include <GLUT/GLUT.h>
#include <math.h>

typedef struct {
	int	w;
	int	a;
	int	s;
	int	d;
	// Button state on or off
} ButtonKeys; ButtonKeys Keys;

//=============================PLAYER=================================//
float	px,py,pdx,pdy,pa;  // Player Position

// Degree to Radian
float DegtoRad(float a)
{
	return (a*M_PI/180.0);
}

// FIX ANGLE ISSUE, OVERFLOW
float fixang(float a)
{
	if (a > 359)
		a-=360;
	else if (a < 0)
		a+=360;
	return (a);
}

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

//--------------------------------MAP----------------------------------------------//
int mapX = 8, mapY = 8, mapS = 64;
int	map[] = 
{
	1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,1,0,0,1,0,1,
	1,0,0,0,0,0,0,1,
	1,0,1,0,0,1,0,1,
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
/*
==============================Pythagorean Theorem===============================================
								  /|
to find the hypotenuse	-------> / |
								/__|
*/
float	shortest_distance(float ax, float ay, float bx, float by, float ang)
{
	return (sqrt((bx-ax)*(bx-ax) + (by-ay)*(by-ay)));
}
//=========================DRAW 3D MAP==========================================================//
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
			 Second Case
			##############
			#			 # 	If we didn't hit a wall
			#			 # then it means that the wall still far away
			#			 # so in this case we need to try again, but how ?
			#     /  	 #
			#    /   	 #
			#   /		 #
			#  O	 	 #
			##############
			So to fix this
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
			glColor3f(0, 1, 0); // Vertical Wall hit color
		}
		else if (disH < disV)
		{
			rx = hx;
			ry = hy;
			disT = disH;
			glColor3f(0, 0, 1); // Horizontal Wall hit color
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

// Adjust values depending on frame rate
float	frame1, frame2, fps;

void display()
{
	// Frame Per Second
	frame2 = glutGet(GLUT_ELAPSED_TIME);
	fps = (frame2 - frame1);
	frame1 = glutGet(GLUT_ELAPSED_TIME);

	// Buttons 
	if ( Keys.a == 1)
	{
		pa -= 0.1;
		if (pa < 0)
			pa += 2*PI;
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
	}
	if ( Keys.d == 1)
	{
		pa += 0.1;
		if (pa > 2*PI)
			pa -= 2*PI;
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
	}

	// Walls Collisions
	int xo = 0; // xo = x offset infornt of player so we can check walls
	if (pdx < 0)
		xo -= 20;
	else
		xo = 20;

	int yo = 0; // yo = y offset infornt of player so we can check walls
	if (pdy < 0)
		yo -= 20;
	else
		yo = 20;
	
	// ipx = player grid position, ipx_add = position + offset, ipx_sub = position - offset, same for Y
	int ipx=px/64.0, ipx_add_xo=(px+xo)/64.0, ipx_sub_xo=(px-xo)/64.0;
	int ipy=py/64.0, ipy_add_yo=(py+yo)/64.0, ipy_sub_yo=(py-yo)/64.0;

	// To know if there is a wall we update the player movement depnding on the map position + offset in X and Y
	if ( Keys.w == 1)
	{
		if(map[ipy*mapX + ipx_add_xo]==0)
			px += pdx;
		if(map[ipy_add_yo*mapX + ipx]==0)
			py += pdy;
	}
	if ( Keys.s == 1)
	{
		if(map[ipy*mapX + ipx_sub_xo]==0)
			px -= pdx;
		if(map[ipy_sub_yo*mapX + ipx]==0)
			py -= pdy;
	}
	glutPostRedisplay();


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawMap2D();
	draw_player();
	drawRays2D();
	glutSwapBuffers();
}

void init()
{
	glClearColor(0.3, 0.3, 0.3, 0);
	gluOrtho2D(0, 1024, 510, 0);
	px = 300;			py = 300;
	pdx = cos(pa) * 5;	pdy = sin(pa) * 5;
}

void	Buttons_Down(unsigned char key, int x, int y)
{
	// We change button state to 1, when key is down,
	// need to implement this as struct, as the function here is declared as
	// (unsiged char key, int x, int y), we need to play around this in MLX
	// because we cant pass struch here or typcast it
	if (key == 'w')
		Keys.w = 1;
	else if (key == 'a')
		Keys.a = 1;
	else if (key == 's')
		Keys.s = 1;
	else if (key == 'd')
		Keys.d = 1;
	glutPostRedisplay();
}

void	Buttons_Up(unsigned char key, int x, int y)
{
	//We change button state to 0, when key is pressed,
	// need to implement this as struct, as the function here is declared as
	// (unsiged char key, int x, int y), we need to play around this in MLX
	// because we cant pass struch here or typcast it
	if (key == 'w')
		Keys.w = 0;
	else if (key == 'a')
		Keys.a = 0;
	else if (key == 's')
		Keys.s = 0;
	else if (key == 'd')
		Keys.d = 0;
	glutPostRedisplay();
}

void	resize(int w, int h)
{
	//resize window, to fix window scalling issue
	// when stretching window size, it gets unscaled
	// |  |  |  | -->> ||||
	glutReshapeWindow(1024, 510);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1024,510);
	//glutInitWindowPosition(200, 200);
	glutCreateWindow("My Own Game");
	init();
	glutDisplayFunc(display);
	//glutReshapeFunc(resize);
	glutKeyboardFunc(Buttons_Down);
	glutKeyboardUpFunc(Buttons_Up);
	glutMainLoop();
}
