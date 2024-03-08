/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamoha <mohamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 20:01:00 by mohamoha          #+#    #+#             */
/*   Updated: 2023/07/25 18:30:29 by mohamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_copy(char const *str, char *temp, int len, int index)
{
	int		i;

	i = 0;
	while (i < len)
	{
		temp[i] = str[index];
		index++;
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	int		tot_len;
	int		start;
	int		end;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	start = 0;
	end = ft_strlen(s1) -1;
	while (s1[start] != '\0' && ft_strchr(set, s1[start]) != NULL)
	{
		start++;
	}
	while (end >= start && ft_strchr(set, s1[end]) != NULL)
	{
		end--;
	}
	tot_len = end - start + 1;
	trim = malloc(sizeof(char) * tot_len + 1);
	if (!trim)
		return (NULL);
	ft_copy(s1, trim, tot_len, start);
	return (trim);
}
