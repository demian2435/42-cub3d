# gcc .c libft/.c get_next_line/*.c -L minilibx_opengl -l mlx -framework OpenGL -framework AppKit

NAME		= cub3D
MLX			= -Lminilibx/ -lmlx -framework OPENGL -framework Appkit
LIBFT		= -Llibft -lft
SRCS		= main.c
CFLAGS		= -Wall -Wextra -Werror -c
CC			= gcc ${CFLAGS}
RM			= rm -f
OBJS		= ${SRCS:.c=.o}

%.o:		%.c
			${CC} ${CFLAGS} $<

all: libft minilibx ${NAME}

libft:
	make -C libft/

minilibx:
	make -C minilibx/

${NAME}: ${OBJS}
	$(CC) ${LIBFT} ${MLX} -o ${NAME} ${OBJS}  

clean:
			${RM} ${OBJS}
			make -C libft/ clean
			make -C minilibx/ clean

fclean:		clean
			${RM} ${NAME}
			make -C libft/ fclean
			make -C minilibx/ clean

re:			fclean all

.PHONY:		all clean fclean re libft minilibx