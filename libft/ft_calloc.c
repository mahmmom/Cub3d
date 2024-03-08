/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamoha <mohamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:44:44 by mohamoha          #+#    #+#             */
/*   Updated: 2023/07/26 19:51:11 by mohamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nelem, size_t elsize)
{
	void	*ptr;

	if (nelem != 0 && elsize != 0 && nelem > INT_MAX / elsize)
		return (NULL);
	ptr = malloc(nelem * elsize);
	if (ptr != NULL)
		ft_memset(ptr, 0, nelem * elsize);
	return (ptr);
}
