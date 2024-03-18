/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamoha <mohamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:50:34 by mohamoha          #+#    #+#             */
/*   Updated: 2024/03/19 00:16:09 by mohamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_ext(char *input)
{
	if (ft_strchr(input, '.') != NULL)
	{
		input = ft_strchr(input, '.');
		while (!(ft_strncmp(input, ".cub", ft_strlen(input - 4)) == 0))
			return (error_exit(MAP_EXT_ERR), MAP_EXT_ERR);
	}
	return (CORRECT);
}

void	print_texture(t_data *data)
{
	printf("North = %s\n", data->comp.no);
	printf("South = %s\n", data->comp.so);
	printf("East = %s\n", data->comp.es);
	printf("West = %s\n", data->comp.we);
	printf("Ceiling Color = %d\n", data->comp.ceiling);
	printf("Floor Color = %d\n", data->comp.floor);
}

int	check_texture(t_data *data, char **array, char *text)
{
	if (array_size(array) != 2)
	{
		free_array(array);
		return (error_exit(TEXT_ERR), TEXT_ERR);
	}
	if (texture_path(array[1]) == 0)
	{
		free_array(array);
		return (error_exit(TEXT_ERR), TEXT_ERR);
	}
	if ((ft_strncmp(array[0], text, 2) == 0) && !data->comp.no)
		data->comp.no = ft_strdup(array[1]);
	else if ((ft_strncmp(array[0], text, 2) == 0) && !data->comp.so)
		data->comp.so = ft_strdup(array[1]);
	else if ((ft_strncmp(array[0], text, 2) == 0) && !data->comp.we)
		data->comp.we = ft_strdup(array[1]);
	else if ((ft_strncmp(array[0], text, 2) == 0) && !data->comp.es)
		data->comp.es = ft_strdup(array[1]);
	else
	{
		free_array(array);
		return (error_exit(DUP_ERR), DUP_ERR);
	}
	free_array(array);
	return (CORRECT);
}

int	open_file(char *file_name)
{
	int	temp;

	temp = open(file_name, O_DIRECTORY);
	if (temp >= 0)
		return (error_exit(OPEN_ERR), -1);
	temp = open(file_name, O_RDONLY);
	if (temp < 0)
		return (error_exit(OPEN_ERR), -1);
	// check if it's correct in this location or move to another func
	if (check_map_ext(file_name) == 1)
		return (-1);
	return (temp);
}

static int	parse_line(t_data *data, char *map_line)
{
	char	**array;

	array = ft_split(map_line, ' ');
	if (comp_exist(array, "NO"))
		return (check_texture(data, array, "NO"));
	else if (comp_exist(array, "SO"))
		return (check_texture(data, array, "SO"));
	else if (comp_exist(array, "WE"))
		return (check_texture(data, array, "WE"));
	else if (comp_exist(array, "EA"))
		return (check_texture(data, array, "EA"));
	else if (comp_exist(array, "F"))
		return (check_color(data, array, "F"));
	else if (comp_exist(array, "C"))
		return (check_color(data, array, "C"));
	else
	{
		free_array(array);
		return (error_exit(MAP_ERR), MAP_ERR);
	}
	return (CORRECT);
}

int	parse_map(t_data *data, char *file_name)
{
	int		fd;
	char	*line;
	char	*map_line;

	fd = open_file(file_name);
	if (fd == -1)
		return (error_exit(OPEN_ERR), OPEN_ERR);
	line = get_next_line(fd);
	while (line)
	{
		map_line = ft_strtrim(line, " \t\v\f\r\n");
		free(line);
		if (*map_line && parse_line(data, map_line) != CORRECT)
		{
			printf("are we here\n");
			free(map_line);
			return (close(fd), MAP_ERR);
		}
		free(map_line);
		if (all_comp_found(data) == 1)
			{
				print_texture(data);
				break ;
			}
		line = get_next_line(fd);
	}
	//get_map(data, fd);
	return (close(fd), CORRECT);
}
