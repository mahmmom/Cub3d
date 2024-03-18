/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamoha <mohamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:54:56 by wahmed            #+#    #+#             */
/*   Updated: 2024/03/18 20:49:14 by mohamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include<unistd.h>
# include<string.h>
# include<stdlib.h>
# include"../libft/libft.h"

char	*get_next_line(int fd);
int		len(char *s);
t_list	*lst_new(char *content);
char	*join(char *s1, char *s2);
void	add_front(t_list **lst, t_list *neww);
void	add_back(t_list **lst, char *content);
char	*read_lst(t_list **lst);
char	*cut(char *s, unsigned int start, size_t len);
int		line_len(char *s);

#endif