NAME = cub3d

# Add get_next_line.c to the list of source files
SRC =	main.c parsing.c init.c error.c utils.c\
		GNL/get_next_line_bonus.c GNL/get_next_line_utils_bonus.c \
#SRC = Walls_Ceiling_Floor.c
# Update object files to include get_next_line.o
OBJS = $(SRC:.c=.o)

CC = cc

CFLAGS = #-framework OpenGL -framework GLUT -Ilibft -fsanitize=address -g3

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
