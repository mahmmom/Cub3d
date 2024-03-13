ifndef VERPOSE
.SILENT:
endif

NAME = cub3d

# Add get_next_line.c to the list of source files
SRC =	main.c parsing.c init.c error.c utils.c map_parse.c\
		GNL/get_next_line.c GNL/get_next_line_utils.c \
#SRC = Walls_Ceiling_Floor.c
# Update object files to include get_next_line.o
OBJS = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -Ilibft -g3 #-fsanitize=address -g3

#-framework OpenGL -framework GLUT 

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS) | libft
	$(CC) $(OBJS) -Llibft -lft $(CFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

libft:
	make -C libft

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re libft
