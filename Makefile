NAME		= miniRT
SRCSNAME	=	check_environment.c \
				check_objects.c \
				check_space.c \
				event.c \
				export_bmp.c \
				ft_split_multi.c \
				get_next_line_bonus.c \
				intersect_objects.c \
				macros.c \
				minirt.c \
				minirt_utils.c \
				raytrace.c \
				reflection.c \
				set_environment.c \
				set_objects.c \
				set_space.c \
				vector3.c \
				vector3_fourope.c \
				vector3_fourope_utils.c

SRCS		= $(addprefix ./srcs/, $(SRCSNAME))
OBJS		= $(SRCS:.c=.o)
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f
DEBUG		= -g -fsanitize=address

all : $(NAME)

$(NAME) : $(OBJS)
	make -C ./includes/libft
	chmod +x ./includes/minilibx-linux/configure
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
