/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamoha <mohamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:08:36 by mohamoha          #+#    #+#             */
/*   Updated: 2024/03/08 18:21:20 by mohamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"
#include <stdlib.h>

char	*join_args(char **str)
{
	int		i;
	char	*color;

	if(!str || !*str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		color = ft_strjoin(color,str[i]);
		i++;
	}
    free_array(str);
    return (color);
}

int check_args(char **str)
{
    int i;
    int j;

    i = 0;
    while (str[i])
    {
        
    }
}

int	ft_atoi_rgb(char **str)
{
	char	**temp;
	char	*color;
	int		i;
	
	i = 0;
	color = join_args(str);
    temp = ft_split(color, ',');
    free(color);
    if (check_args(temp) == 1)
        return (free_array(temp),error_handler(ERROR_Color, NULL),-1);
	return (0);
}
