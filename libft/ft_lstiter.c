/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamoha <mohamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:32:19 by mohamoha          #+#    #+#             */
/*   Updated: 2023/07/25 18:28:41 by mohamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*ptr;
	t_list	*temp;

	if (!lst ||!f)
		return ;
	ptr = lst;
	while (ptr != NULL)
	{
		temp = ptr->next;
		(f)(ptr->content);
		ptr = temp;
	}
}
