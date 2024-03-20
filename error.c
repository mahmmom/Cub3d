/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wahmed <wahmed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:26:36 by wahmed          #+#    #+#             */
/*   Updated: 2024/03/20 16:13:43 by wahmed        ###   ########.fr       */
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

void	clean_exit(t_data *data)
{
	if (data->comp.no)
		free(data->comp.no);
	if (data->comp.so)
		free(data->comp.so);
	if (data->comp.we)
		free(data->comp.we);
	if (data->comp.es)
		free(data->comp.es);
	if (data->map.map_data)
		free_array(data->map.map_data);
	exit(EXIT_FAILURE);
}

void	print_error(char *msg)
{
	printf("Error\n");
	printf("%s\n", msg);
}

void	error_exit(enum e_error	value)
{
	if (value == ARG_ERR)
		return (print_error(E_ARG));
	else if (value == MAP_EXT_ERR)
		return (print_error(E_MAP_EXT));
	else if (value == TEXT_ERR)
		return (print_error(E_TEXT));
	else if (value == TEXT_PATH_ERR)
		return (print_error(E_TEXT_PATH));
	else if (value == COLOR_ERR)
		return (print_error(E_COLOR));
	else if (value == MALLOC_ERR)
		return (print_error(E_MALLOC));
	else if (value == OPEN_ERR)
		return (print_error(E_OPEN));
	else if (value == MAP_ERR)
		return (print_error(E_MAP));
	else if (value == DUP_ERR)
		return (print_error(E_DUPLICATE));
	else if (value == EMPTY_ERR)
		return (print_error(E_EMPTY));
	else
		return (print_error(E_INVALID));
}

// void free_ptr(void **ptr)
// {
//     if (*ptr != NULL)
// 	{
//         free(*ptr);
//         *ptr = NULL;
//     }
// }