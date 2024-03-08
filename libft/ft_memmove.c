/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamoha <mohamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:46:08 by mohamoha          #+#    #+#             */
/*   Updated: 2023/07/26 20:57:26 by mohamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*temp;
	char	*ft_dest;

	temp = (char *)src;
	ft_dest = (char *)dest;
	if (temp < ft_dest)
	{
		while (n--)
		{
			ft_dest[n] = temp[n];
		}
	}
	else
	{
		ft_memcpy(ft_dest, temp, n);
	}
	return (dest);
}
