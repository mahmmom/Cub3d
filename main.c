/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamoha <mohamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:28:18 by mohamoha          #+#    #+#             */
/*   Updated: 2024/03/08 19:03:36 by mohamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_args()
{
	printf("%s", ERROR_ARGS);
	exit(EXIT_FAILURE);
}

void	init_data(t_data *data)
{
	data->comp.no = NULL;
	data->comp.so = NULL;
	data->comp.we = NULL;
	data->comp.es = NULL;
	data->comp.floor = -1;
	data->comp.ceiling = -1;
	data->comp.file.fd = 0;
	data->comp.file.l_n = 0;
	data->comp.file.line = NULL;
	data->comp.file.f_2d = NULL;
	data->comp.map.map_2d = NULL;
	data->comp.map.map_h = 0;
	data->comp.map.map_w = 0;
	data->comp.map.map_h = 0;
	data->comp.map.p_dir = 0;
	data->comp.map.p_pos = 0;
}


int main(int ac, char **av)
{
	t_data	data;

	init_data(&data);
	if (ac != 2)
        error_args();
	data.comp.file.fd = open(av[1], O_DIRECTORY);
	if (data.comp.file.fd >= 0)
		error_handler("Argument cannot be a directory", &data);
	data.comp.file.fd = open(av[1], O_RDONLY);
	check_map_ext(av[1], &data);
	parse_map(&data);
	//data = init_args();
	//free_data(&data);
	close(data.comp.file.fd);
}
