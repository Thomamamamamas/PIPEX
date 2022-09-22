NAME	= pipex

SRCS	= $(wildcard srcs/*.c)

OBJS	= $(SRCS:.c=.o)

HEADER	= includes

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
RM		= rm -f

all :		$(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I.srcs/libftprintf/libftprintf.a -c $< -o $@

$(NAME) :	$(OBJS) libftprintf
			$(CC) $(OBJS) ./srcs/libftprintf/libftprintf.a -o $(NAME)

libftprintf:
		$(MAKE) -C ./srcs/libftprintf
		cp srcs/libftprintf/libftprintf.a $(NAME)

clean :
		$(MAKE) -C ./srcs/libftprintf $@
		$(RM) $(OBJS)

fclean :	clean
	$(MAKE) -C ./srcs/libftprintf $@
			$(RM) $(NAME)

re :		fclean all

.PHONY :	all clean fclean re libftprintf
