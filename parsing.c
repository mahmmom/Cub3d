/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamoha <mohamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:50:34 by mohamoha          #+#    #+#             */
/*   Updated: 2024/03/14 19:37:18 by mohamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_map_ext(char *input, t_data *data)
{
	if (ft_strchr(input, '.') != NULL)
	{
		input = ft_strchr(input, '.');
		while (!(ft_strncmp(input, ".cub", ft_strlen(input - 4)) == 0))
			error_handler(ERROR_MAP_EXT, data);
	}
	if (data->comp.file.fd < 0)
		error_handler("Invalid Map File", data);
}

void	print_texture(t_data *data)
{
	printf("North = %s\n", data->comp.no);
	printf("South = %s\n", data->comp.so);
	printf("East = %s\n", data->comp.es);
	printf("West = %s\n", data->comp.we);
}

void	remove_newline(char **str)
{
	int		len;
	char	*tmp;

	tmp = str[0];
	len = ft_strlen(tmp);
	if (len > 0 && tmp[len - 1] == '\n')
		tmp[len - 1] = '\0';
}

// void	remove_newline(char **str)
// {
// 	char *new_l;
// 	if(str == NULL || *str == NULL)
// 		return ;
// 	new_l = ft_strchr(*str,'\n');
// 	if(new_l != NULL)
// 		*new_l = '\0';
// }

int	is_map_char(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j] != '\0')
		{
			if (str[i][j] != 'N' && str[i][j] != 'S' && str[i][j] != 'E'
				&& str[i][j] != 'W' && str[i][j] != '0' && str[i][j] != '1')
			{
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_texture(t_data *data)
{
	if ((ft_strncmp(data->comp.file.f_2d[0], "NO", 2) == 0) && !data->comp.no
		&& data->comp.file.f_2d[1] && !data->comp.file.f_2d[2])
		data->comp.no = ft_strdup(data->comp.file.f_2d[1]);
	else if ((ft_strncmp(data->comp.file.f_2d[0], "SO", 2) == 0)
		&& !data->comp.so && data->comp.file.f_2d[1]
		&& !data->comp.file.f_2d[2])
		data->comp.so = ft_strdup(data->comp.file.f_2d[1]);
	else if (ft_strncmp(data->comp.file.f_2d[0], "EA", 2) == 0 && !data->comp.es
		&& data->comp.file.f_2d[1] && !data->comp.file.f_2d[2])
		data->comp.es = ft_strdup(data->comp.file.f_2d[1]);
	else if (ft_strncmp(data->comp.file.f_2d[0], "WE", 2) == 0 && !data->comp.we
		&& data->comp.file.f_2d[1] && !data->comp.file.f_2d[2])
		data->comp.we = ft_strdup(data->comp.file.f_2d[1]);
	else if (data->comp.ceiling == -1 && ft_strncmp(data->comp.file.f_2d[0],
			"C", 1) == 0)
		data->comp.ceiling = ft_atoi_rgb(data, data->comp.file.f_2d + 1);
	else if (data->comp.floor == -1 && ft_strncmp(data->comp.file.f_2d[0], "F",
			1) == 0)
		data->comp.floor = ft_atoi_rgb(data, data->comp.file.f_2d + 1);
	else
		return (1);
	return (0);
}

void	get_map_textures(t_data *data)
{
	// check if map is empty, need to make function
	// if(data->comp.file.line == NULL)
	// 	printf("Error\nMap is Empty\n");
	while ((data->comp.file.line = get_next_line(data->comp.file.fd)) != NULL)
	{
		remove_newline(&data->comp.file.line);
		data->comp.file.f_2d = ft_split(data->comp.file.line, ' ');
		// free(data->comp.file.line);
		if (!data->comp.file.f_2d || !*data->comp.file.f_2d
			|| data->comp.file.f_2d[0][0] == '\0')
		{
			free_array(data->comp.file.f_2d);
			continue ;
		}
		if (check_texture(data) == 1)
		{
			if (is_map_char(data->comp.file.f_2d) == 1)
			{
				print_texture(data);
				free_array(data->comp.file.f_2d);
				// free(data->comp.file.line);
				break ;
			}
			else
				error_handler("Invalid Identifier", data);
		}
		free_array(data->comp.file.f_2d);
	}
	// printf("last line = [%s]\n", data->comp.file.line);
}

void	ft_array(t_data *data)
{
	int	i;

	i = 0;
	while ((data->comp.file.line = get_next_line(data->comp.file.fd)) != NULL)
	{
		data->temp_map = (char **)ft_realloc(data->temp_map, i * sizeof(char *),
				(i + 2) * sizeof(char *));
		if (data->temp_map == NULL)
		{
            error_handler("Memory allocation failed", data);
            return;
		}
		data->temp_map[i] = ft_strdup(data->comp.file.line);
		free(data->comp.file.line);
		i++;
	}
	free(data->comp.file.line);
	printf("I = %d\n", i);
	data->temp_map[i+1] = NULL;
}

void	parse_map(t_data *data)
{
	data->comp.file.fd = open(data->input_map, O_DIRECTORY);
	if (data->comp.file.fd >= 0)
		error_handler("Argument cannot be a directory", data);
	data->comp.file.fd = open(data->input_map, O_RDONLY);
	check_map_ext(data->input_map, data);
	ft_array(data);
	//print_array(data->temp_map);
	//get_map_textures(data);
	// get_map(data);
	close(data->comp.file.fd);
}
