/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamoha <mohamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:03:38 by mohamoha          #+#    #+#             */
/*   Updated: 2024/03/20 21:57:05 by mohamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(new_size));
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
	{
		free(ptr);
		return (NULL);
	}
	ft_memcpy(new_ptr, ptr, old_size);
	free(ptr);
	return (new_ptr);
}

char	**re_build_map(int fd)
{
	char	**temp_map;
	char	*line;
	int		i;

	i = -1;
	line = get_next_line(fd);
	if (!line)
		return (NULL);
	temp_map = NULL;
	while (line)
	{
		i++;
		temp_map = (char **)ft_realloc(temp_map, i * sizeof(char *), (i + 2)
				* sizeof(char *));
		if (temp_map == NULL)
			return (free(line), NULL);
		temp_map[i] = ft_strdup(line);
		free(line);
		if (!temp_map[i])
			return (free_array(temp_map), NULL);
		line = get_next_line(fd);
	}
	temp_map[i+1] = NULL;
	return (temp_map);
}

char	**parse_new_map(char **map)
{
	char	**temp_map;
	int		i;
	int		count;

	i = 0;
	count = -1;
	temp_map = NULL;
	while(is_empty_line(map[i]) == 1)
		i++;
	while (map[i] && is_empty_line(map[i]) == 0)
	{
		if (is_empty_line(map[i]) == 1)
			return (NULL);
		count++;
		temp_map = (char **)ft_realloc(temp_map, i * sizeof(char *), (count + 2)
				* sizeof(char *));
		if (temp_map == NULL)
			return (NULL);
		temp_map[count] = ft_strdup(map[i]);
		//printf("count = [%d]temp count = [%s]\n", count, temp_map[count]);
		// free(map[i]);
		if (!temp_map[count])
			return (free_array(temp_map), NULL);
		i++;
	}
	temp_map[count] = NULL;
	return (temp_map);
}

int	get_map(t_data *data, int fd)
{
	char	**temp_map;

	// int i;
	// i = 0;
	(void)data;
	temp_map = re_build_map(fd);
	if (!temp_map)
		return (error_exit(MALLOC_ERR), MALLOC_ERR);
	temp_map = parse_new_map(temp_map);
	print_array(temp_map);
	free_array(temp_map);
	return (CORRECT);
}
