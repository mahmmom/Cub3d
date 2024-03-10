/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamoha <mohamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:50:34 by mohamoha          #+#    #+#             */
/*   Updated: 2024/03/08 19:07:30 by mohamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_map_ext(char *input_map, t_data *data)
{
	if (ft_strchr(input_map, '.') != NULL)
		input_map = ft_strchr(input_map, '.');
	else
		error_handler(ERROR_MAP_EXT, data);
	if (!(ft_strncmp(input_map, ".cub",4) == 0)
		|| data->comp.file.fd < 0)
		error_handler(ERROR_MAP_EXT, data);
}

void	print_texture(t_data *data)
{
	printf("North = %s\n",  data->comp.north);
	printf("South = %s\n",  data->comp.south);
	printf("East = %s\n",  data->comp.east);
	printf("West = %s\n",  data->comp.west);
}

void remove_newline(char **str)
{
    int		len;
	char	*tmp;
	
	tmp = str[0];
	len = ft_strlen(tmp);
    if (len > 0 && tmp[len - 1] == '\n')
        tmp[len - 1] = '\0';
}

void get_map_textures(t_data *data)
{
    while ((data->comp.file.line = get_next_line(data->comp.file.fd)) != NULL)
    {
        remove_newline(&data->comp.file.line);
        data->comp.file.file_2d = ft_split(data->comp.file.line, ' ');
        free(data->comp.file.line);
        if (!data->comp.file.file_2d || !*data->comp.file.file_2d || data->comp.file.file_2d[0][0] == '\0')
        {
            free_array(data->comp.file.file_2d);
            continue;
        }
        if (ft_strncmp(data->comp.file.file_2d[0], "NO", 2) == 0 && data->comp.north == NULL)
            data->comp.north = ft_strdup(data->comp.file.file_2d[1]);
        else if (ft_strncmp(data->comp.file.file_2d[0], "SO", 2) == 0 && data->comp.south == NULL)
            data->comp.south = ft_strdup(data->comp.file.file_2d[1]);
        else if (ft_strncmp(data->comp.file.file_2d[0], "EA", 2) == 0 && data->comp.east == NULL)
            data->comp.east = ft_strdup(data->comp.file.file_2d[1]);
        else if (ft_strncmp(data->comp.file.file_2d[0], "WE", 2) == 0 && data->comp.west == NULL)
            data->comp.west = ft_strdup(data->comp.file.file_2d[1]);
        else if (ft_strncmp(data->comp.file.file_2d[0], "C", 1) == 0)
        {
            data->comp.ceiling = ft_atoi_rgb(data, data->comp.file.file_2d + 1);
            printf("Ceiling color = %d\n", data->comp.ceiling);
        }
        else if (ft_strncmp(data->comp.file.file_2d[0], "F", 1) == 0)
        {
            print_texture(data);
            break;
        }
        else
            error_handler("Invalid Identifier", data);
        free_array(data->comp.file.file_2d);
    }
}

void	parse_map(t_data *data)
{
	get_map_textures(data);
	//get_map();
}
