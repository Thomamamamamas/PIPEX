NAME	= pipex

SRCS	= $(wildcard srcs/*.c)

OBJS	= $(SRCS:.c=.o)

HEADER	= includes

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
RM		= rm -f

all :		$(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I.srcs/libftprintf/libftprintf.a -I.srcs/get_next_line/get_next_line.a -c $< -o $@

$(NAME) :	$(OBJS) libftprintf get_next_line
			$(CC) $(OBJS) ./srcs/libftprintf/libftprintf.a ./srcs/get_next_line/get_next_line.a -o $(NAME)

libftprintf:
		$(MAKE) -C ./srcs/libftprintf
		cp srcs/libftprintf/libftprintf.a $(NAME)

get_next_line:
		$(MAKE) -C ./srcs/get_next_line
		cp srcs/get_next_line/get_next_line.a $(NAME)

clean :
		$(MAKE) -C ./srcs/libftprintf $@
		$(MAKE) -C ./srcs/get_next_line $@
		$(RM) $(OBJS)

fclean :	clean
	$(MAKE) -C ./srcs/libftprintf $@
	$(MAKE) -C ./srcs/get_next_line $@
	$(RM) $(NAME)

re :		fclean all

.PHONY :	all clean fclean re libftprintf get_next_line
