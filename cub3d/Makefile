OS			= $(shell uname)

NAME		= Cub3D

MAP			= ./maps/map.cub

CC			= gcc

OPT			= -O3

FLAGS		= -Wall -Wextra -Werror

SRCS		= main.c

OBJS		= ${SRCS:.c=.o}

ifeq ($(OS), Linux)
	MLX_DIR	= minilibx-linux
	MLX_LNK	= -L ${MLX_DIR} -lmlx -lXext -lX11 -lbsd
else
	MLX_DIR	= minilibx-opengl
	MLX_LNK	= -L ${MLX_DIR} -lmlx -framework OpenGL -framework AppKit 
endif

FT_DIR = libft
FT_LNK = -L ${FT_DIR} -lft

INC = -I $(FT_DIR) -I $(MLX_DIR)

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} ${INC}

${NAME}: ${OBJS} ft mlx
		${CC} ${OPT} ${CFLAGS} ${INC} ${OBJS} ${FT_LNK} ${MLX_LNK} -o ${NAME}

mlx:
	make -C ${MLX_DIR}

ft:
	make -C ${FT_DIR}

all: ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	make fclean -C ${FT_DIR}
	make clean -C ${MLX_DIR}
	rm -f ${NAME}

re: fclean all

run: ${NAME}
		./${NAME} ${MAP}

v: ${NAME}
	valgrind --leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--verbose \
	--log-file=./extra/valgrind-out.txt \
	./${NAME} ${MAP} && cat ./extra/valgrind-out.txt

.PHONY: all clean fclean re mlx ft run v