/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamoha <mohamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:54:56 by wahmed            #+#    #+#             */
/*   Updated: 2024/03/14 15:58:44 by mohamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

size_t		ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_str_init(void);
char	*ft_strjoin_mod(char *s1, char *s2);
char	*ft_read(int fd, char *str);
char	*ft_skip(char *str);
char	*ft_line(char *str);
char	*get_next_line(int fd);

#endif
