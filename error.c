/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamoha <mohamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:26:36 by mohamoha          #+#    #+#             */
/*   Updated: 2024/03/08 19:09:12 by mohamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_array(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		free(str[i++]);
	if (str)
		free(str);
}

void	free_data(t_data *data)
{
	free_array(data->comp.file.file_2d);
	//cu_free_2d(data->comp.map.map_2d);
	if (data->comp.file.line)
		free(data->comp.file.line);
	if (data->comp.north)
		free(data->comp.north);
	if (data->comp.south)
		free(data->comp.south);
	if (data->comp.west)
		free(data->comp.west);
	if (data->comp.east)
		free(data->comp.east);
}

void	error_handler(char *msg, t_data *data)
{
	printf("Error\n");
	printf("%s\n", msg);
	if (data->comp.file.fd > 0)
		close(data->comp.file.fd);
	free_data(data);
	exit (1);
}
