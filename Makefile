NAME = miniRT
SRCSNAME =	minirt.c \
			minirt_raytrace.c \
			minirt_utils.c \
			intersect_objects.c \
			reflection.c \
			check_environment.c \
			check_objects.c \
			check_space.c \
			set_environment.c \
			set_objects.c \
			set_space.c \
			get_next_line_bonus.c \
			vector3.c \
			debug.c

SRCS	= $(addprefix ./srcs/, $(SRCSNAME))
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
DEBUG = -fsanitize=address

all : $(NAME)

$(NAME) : $(OBJS)
	make -C ./includes/libft
	make -C ./includes/minilibx-linux
	cp ./includes/libft/libft.a ./
	cp ./includes/minilibx-linux/libmlx_Linux.a ./
	$(CC) $(CFLAGS) $(DEBUG) $(OBJS) -L. -lm -lft -lmlx_Linux -lXext -lX11 -o $(NAME)

clean :
	$(RM) $(OBJS) libft.a libmlx_Linux.a
	make clean -C ./includes/libft
	make clean -C ./includes/minilibx-linux

fclean : clean
	$(RM) $(NAME)
	make fclean -C ./includes/libft

re : fclean all

.PHONY : $(NAME) all clean fclean re
