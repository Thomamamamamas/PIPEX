NAME	= pipex

SRCS	= $(wildcard *.c)

OBJS	= $(SRCS:.c=.o)

HEADER	= includes

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
RM		= rm -f

all :		$(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME) :	$(OBJS)
			$(CC) -o $(NAME) $(OBJS)

clean :
			$(RM) $(OBJS)

fclean :	clean
			$(RM) $(NAME)

re :		fclean all

.PHONY :	all clean fclean re
