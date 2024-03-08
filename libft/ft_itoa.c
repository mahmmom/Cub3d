/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamoha <mohamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:42:02 by mohamoha          #+#    #+#             */
/*   Updated: 2023/07/26 20:04:04 by mohamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_result(int len, char *str, int nbr, int negative)
{
	str[len] = '\0';
	while (len > negative)
	{
		len--;
		str[len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (str);
}

static int	count_int_len(int nbr)
{
	int	size;

	size = 0;
	if (nbr <= 0)
		size++;
	while (nbr != 0)
	{
		size++;
		nbr /= 10;
	}
	return (size);
}

char	*ft_itoa(int nbr)
{
	char	*str;
	int		negative;
	int		int_size;

	int_size = count_int_len(nbr);
	if (nbr == 0)
		return (ft_strdup("0"));
	if (nbr == -2147483648)
		return (ft_strdup("-2147483648"));
	negative = 0;
	if (nbr < 0)
	{
		negative = 1;
		nbr = -nbr;
	}
	str = (char *)malloc(sizeof(char) * (int_size + 1));
	if (!str)
		return (NULL);
	ft_result(int_size, str, nbr, negative);
	if (negative)
		str[0] = '-';
	return (str);
}
