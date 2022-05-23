NAME	= pipex

SRCS	= pipex.c

OBJS	= ${SRCS:.c=.o}

HEADER	= includes

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
RM		= rm -f

%.o: %.c
	${CC} ${CFLAGS} $< -o $@

all :		${NAME}

${NAME} :	${OBJS}
			${CC} ${OBJS} -o ${NAME}

clean :		${RM} ${OBJS}

fclean :	clean
			${RM} ${NAME}

re :		fclean all

.PHONY :	all clean fclean re
