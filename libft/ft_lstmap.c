/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamoha <mohamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 19:35:03 by mohamoha          #+#    #+#             */
/*   Updated: 2023/07/27 19:04:55 by mohamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*elem;

	if (!lst)
		return (NULL);
	new_lst = 0;
	while (lst)
	{
		elem = ft_lstnew(f(lst->content));
		if (!elem)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, elem);
		lst = lst->next;
	}
	return (new_lst);
}

void	del(void *content)
{
	if(content)
	{
		free(content);
	}
}

void	*ft_capitalize(void *str)
{
	if(!str)
		return (NULL);
	int len = ft_strlen(str) + 1;
	int i = 0;
	char *origin = (char *)str;
	char *str_cap = (char *)malloc(len);
	if(!str_cap)
		return (NULL);
	while (origin[i])
	{
		if (origin[i] >= 'a' && origin[i] <= 'z')
		{
			str_cap[i] = origin[i] - 32;
		}
		i++;
	}
	str_cap[len] = '\0';
	return (str_cap);
}

int main()
{
    t_list *head = ft_lstnew(ft_strdup("a"));
    head->next = ft_lstnew(ft_strdup("b"));
    head->next->next = ft_lstnew(ft_strdup("c"));

    t_list *current = head;
    while (current != NULL)
    {
        printf("%s\n", (char *)current->content);
        current = current->next;
    }

	printf("=====================\n");

    t_list	*headnew;
	headnew = ft_lstmap(head, ft_capitalize, del);
	
    while (headnew != NULL)
    {
        printf("%s\n", (char *)headnew->content);
        headnew = headnew->next;
    }

	t_list *current_free = current;
	while (current != NULL)
	{
		t_list *temp = current_free;
		current_free = current_free->next;
		free(temp->content);
		free(temp);
	}
    return 0;
}