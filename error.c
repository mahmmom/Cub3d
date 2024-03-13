/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamoha <mohamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:26:36 by mohamoha          #+#    #+#             */
/*   Updated: 2024/03/13 16:45:25 by mohamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_array(char **str)
{
	int	i;

	i = 0;
	if(!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
}

void	free_data(t_data *data)
{
	//free_array(data->comp.file.f_2d);
	//cu_free_2d(data->comp.map.map_2d);
	// if (data->comp.file.line)
	// 	free(data->comp.file.line);
	if (data->comp.no)
		free(data->comp.no);
	if (data->comp.so)
		free(data->comp.so);
	if (data->comp.we)
		free(data->comp.we);
	if (data->comp.es)
		free(data->comp.es);
}

void	error_handler(char *msg, t_data *data)
{
	printf("Error\n");
	printf("%s\n", msg);
	free_data(data);
	if (data->comp.file.fd > 0)
		close(data->comp.file.fd);
	exit (1);
}
