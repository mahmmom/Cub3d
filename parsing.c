/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamoha <mohamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:50:34 by mohamoha          #+#    #+#             */
/*   Updated: 2024/03/20 22:59:06 by mohamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_ext(char *input)
{
	if (ft_strchr(input, '.') != NULL)
	{
		input = ft_strchr(input, '.');
		while (!(ft_strncmp(input, ".cub", ft_strlen(input - 4)) == 0))
			return (MAP_EXT_ERR);
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

int	check_texture(t_data *data, char **array)
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
	if ((ft_strncmp(array[0], "NO", 2) == 0) && !data->comp.no)
		data->comp.no = ft_strdup(array[1]);
	else if ((ft_strncmp(array[0], "SO", 2) == 0) && !data->comp.so)
		data->comp.so = ft_strdup(array[1]);
	else if ((ft_strncmp(array[0], "WE", 2) == 0) && !data->comp.we)
		data->comp.we = ft_strdup(array[1]);
	else if ((ft_strncmp(array[0], "EA", 2) == 0) && !data->comp.es)
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

	if (check_map_ext(file_name) != CORRECT)
		return (error_exit(MAP_EXT_ERR), -1);
	temp = open(file_name, O_DIRECTORY);
	if (temp >= 0)
		return (error_exit(OPEN_ERR), -1);
	temp = open(file_name, O_RDONLY);
	if (temp < 0)
		return (error_exit(OPEN_ERR), -1);
	return (temp);
}

static int	parse_line(t_data *data, char *map_line)
{
	char	**array;

	array = ft_split(map_line, ' ');
	if (comp_exist(array, "NO"))
		return (check_texture(data, array));
	else if (comp_exist(array, "SO"))
		return (check_texture(data, array));
	else if (comp_exist(array, "WE"))
		return (check_texture(data, array));
	else if (comp_exist(array, "EA"))
		return (check_texture(data, array));
	else if (comp_exist(array, "F"))
		return (check_color(data, array));
	else if (comp_exist(array, "C"))
		return (check_color(data, array));
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
		return (OPEN_ERR);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), error_exit(EMPTY_ERR), EMPTY_ERR);
	while (line)
	{
		map_line = ft_strtrim(line, " \t\v\f\r\n");
		free(line);
		if (*map_line && parse_line(data, map_line) != CORRECT)
			return (free(map_line), close(fd), MAP_ERR);
		free(map_line);
		if (all_comp_found(data) == 1)
				break ;
		line = get_next_line(fd);
	}
	// if(get_map(data, fd) != CORRECT)
	// 	return (close(fd), MAP_ERR);
	return (close(fd), CORRECT);
}
