# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: d2435 <d2435@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/12 23:27:18 by d2435             #+#    #+#              #
#    Updated: 2021/02/12 23:27:18 by d2435            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS			=	$(shell uname)

NAME		=	Cub3D

MAP			=	./maps/map.cub

CC			=	gcc

OPT			=	-O3

CFLAGS		=	-Wall -Wextra -Werror

SRCS		=	main.c \
				save.c \
				control.c \
				frame.c \
				frame_bis.c \
				parse.c \
				parse_bis.c \
				utils.c \
				sprite.c \
				keys.c \
				player.c \
				print.c \
				move.c

OBJS		=	${SRCS:.c=.o}

ifeq ($(OS), Linux)
MLX_DIR		=	minilibx-linux
MLX_LNK		=	-L ${MLX_DIR} -lmlx -lXext -lX11 -lbsd -lm
else
MLX_DIR		=	minilibx-mac
MLX_LNK		=	-L ${MLX_DIR} -lmlx -framework OpenGL -framework AppKit -lm
endif

FT_DIR 		=	libft
FT_LNK 		=	-L ${FT_DIR} -lft

INC 		=	-I $(FT_DIR) -I $(MLX_DIR)

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o} ${INC}

${NAME}: 	${OBJS} ft mlx
			${CC} ${OPT} ${CFLAGS} ${INC} ${OBJS} ${FT_LNK} ${MLX_LNK} -o ${NAME}

ifeq ($(OS), Linux)
mlx:
			make -C ${MLX_DIR}
else
mlx:
			make -C ${MLX_DIR}
			mv ${MLX_DIR}/libmlx.dylib .
endif

ft:
			make -C ${FT_DIR}

all: 		${NAME}

clean:
			rm -f ${OBJS}

fclean: 	clean
			make fclean -C ${FT_DIR}
			make clean -C ${MLX_DIR}
			rm -f ${NAME}
			rm -f libmlx.dylib

re: 		fclean all

run: 		${NAME}
			./${NAME} ${MAP}

v: 			${NAME}
			valgrind --leak-check=full \
			--show-leak-kinds=all \
			--track-origins=yes \
			--verbose \
			--verbose \
			--log-file=./valgrind-out.txt \
			./${NAME} ${MAP} && cat ./valgrind-out.txt

v_save: 	${NAME}
			valgrind --leak-check=full \
			--show-leak-kinds=all \
			--track-origins=yes \
			--verbose \
			--verbose \
			--log-file=./valgrind-out.txt \
			./${NAME} ${MAP} --save && cat ./valgrind-out.txt

save:  		${NAME}
			./${NAME} ${MAP} --save

.PHONY: 	all clean fclean re mlx ft run v save v_save