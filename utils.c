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


void	join_args(char **str)
{
	int		i;
	char	*color;

	if(!str || !*str)
		return ;
	i = 0;
	while (str[i])
	{
		color = ft_strjoin(color,str[i]);
		printf("Joined = [%s]\n", color);
		i++;
	}
}

int	ft_atoi_rgb(char **str)
{
	char	**temp;
	char	*color;
	int		i;
	
	i = 0;
	color = ft_strdup("");
	while (str[i])
	{
		color = ft_strjoin(color,str[i]);
		printf("Joined = [%s]\n", str[i]);
		i++;
	}
	return (0);
}
