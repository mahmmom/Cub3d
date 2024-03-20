ifndef VERPOSE
.SILENT:
endif

NAME = cub3d

SRC =	main.c init.c error.c parsing.c color.c parsing_utils.c parsing_utils2.c map_parse.c map_parse_utils.c\
		GNL/get_next_line.c GNL/get_next_line_utils.c \

OBJS = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -Ilibft -g3 -fsanitize=address

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS) libft/libft.a
	$(CC) $(OBJS) $(CFLAGS) -Llibft -lft -o $(NAME)

%.o: %.c libft/libft.h
	$(CC) $(CFLAGS) -c $< -o $@

libft/libft.a:
	make -C libft

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re libft/libft.a
