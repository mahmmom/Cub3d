/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamoha <mohamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:28:23 by mohamoha          #+#    #+#             */
/*   Updated: 2024/03/08 18:57:15 by mohamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "GNL/get_next_line.h"
# include "libft/libft.h"
# include "minilibx/mlx.h" // MLX library
// # include <GLUT/GLUT.h>
// # include <GLUT/glut.h>
// # include <OpenGL/OpenGL.h>
// # include <OpenGL/gl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define ERROR_ARGS "Error\nPlease Enter: ./cub3d maps/*.cub\n"
# define ERROR_MAP_EXT "Invalid Map file extension\nPlease Enter: *.cub"
# define ERROR_Color "Invalid Color\n"

# define PI 3.1415926535
# define PI2 PI / 2
# define PI3 3 * PI / 2
# define DR 0.0174533 // 1 Degree to RAD

# define EPSILON 0.0001

typedef struct s_map
{
	char	**map_2d;
	int		map_w;
	int		map_h;
	int		p_pos;
	char	p_dir;
}	t_map;

typedef struct s_file
{
	int		fd;
	int		l_n;
	char	*line;
	char	**f_2d;
}				t_file;

typedef struct s_comp
{
	t_map	map;
	t_file	file;
	char	*no;
	char	*so;
	char	*we;
	char	*es;
	int		floor;
	int		ceiling;
}				t_comp;

typedef struct s_data
{
	char	**map2d; 		// the map
	char	**texture;      // the map texture
	char	**color;		// the map color
	int		p_x;     		// player x position in the map
	int		p_y;     	    // player y position in the map
	int		w_map;    		// map width
	int		h_map;    		// map height
	int		fd;
	t_comp	comp;
}		t_data;


// Parsing
void	check_map_ext(char *input_map, t_data *data);
void	parse_map(t_data *data);
void	remove_newline(char **str);
void    get_map(t_data *data);
int		is_map_char(char *str);
//Colors
int		ft_atoi_rgb(t_data *data, char **str);

// Initialize
t_data	*init_args(void);

// Error handler
void	error_handler(char *msg, t_data *data);
void	free_data(t_data *data);
void	free_array(char **str);

#endif