OUT = pipex

SRC = src/pipex.c src/pipex_utils.c

OBJS = ${SRC:.c=.o}

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g
INCLUDE = -I includes
MAKE = make -C
LIBFT_PATH = libft
LIBFT = -L ${LIBFT_PATH} -lft

#valgrind --leak-check=full --trace-children=yes

.c.o:
		${CC} ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}

$(OUT): ${OBJS}
		${MAKE} ${LIBFT_PATH} all
		${CC} ${OBJS} ${LIBFT} -o ${OUT}

all:	${OUT}

clean:
		${MAKE} ${LIBFT_PATH} clean
		${RM} ${OBJS}

fclean: clean
		${MAKE} ${LIBFT_PATH} fclean
		${RM} ${OUT}

re: fclean all

.PHONY: all clean fclean re
