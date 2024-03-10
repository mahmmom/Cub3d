/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamoha <mohamoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:59:16 by mohamoha          #+#    #+#             */
/*   Updated: 2023/08/16 20:54:09 by mohamoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100000000
# endif

struct s_queue_node {
	char				val;
	struct s_queue_node	*next;
};

typedef struct s_queue_node	t_queue_node;

typedef struct s_queue{
	t_queue_node	*front;
	t_queue_node	*rear;
}	t_queue;

void	enqueue(t_queue *q, const char *data, size_t length);
char	*dequeue_all(t_queue *q);
char	dequeue(t_queue *q);
int		queue_is_empty(t_queue *q);
int		queue_length(t_queue *q);
char	*get_next_line(int fd);
char	*dequeue_until_newline(t_queue *q);
char	*dequeue_last_line(t_queue *q);
char	*save_queue(ssize_t bytes, t_queue *q, char *buffer, int *fd);
int		check_newline(t_queue *q);

#endif