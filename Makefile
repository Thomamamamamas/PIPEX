NAME		= pipex

SRCS		= srcs/main.c \
				srcs/pipex.c \
				srcs/errors_gestion.c \
				srcs/parsing.c \
				srcs/utils.c

SRCS_BONUS	= srcs/main_bonus.c \
				srcs/pipex.c \
				srcs/pipex_multi_pipes.c \
				srcs/errors_gestion.c \
				srcs/parsing_bonus.c \
				srcs/parsing.c \
				srcs/utils_multi_pipes.c \
				srcs/utils2_multi_pipes.c \
				srcs/utils.c

OBJS		= $(SRCS:.c=.o)

OBJS_BONUS	= $(SRCS_BONUS:.c=.o)

HEADER		= includes

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra
RM			= rm -f

all :		$(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I.srcs/libftprintf/libftprintf.a -I.srcs/get_next_line/get_next_line.a -c $< -o $@

$(NAME) :	$(OBJS) ./srcs/libftprintf/libftprintf.a ./srcs/get_next_line/get_next_line.a
			$(CC) $(OBJS) ./srcs/libftprintf/libftprintf.a ./srcs/get_next_line/get_next_line.a -o $(NAME)

bonus:		$(OBJS_BONUS) ./srcs/libftprintf/libftprintf.a ./srcs/get_next_line/get_next_line.a
			$(CC) $(OBJS_BONUS) ./srcs/libftprintf/libftprintf.a ./srcs/get_next_line/get_next_line.a -o $(NAME)

./srcs/libftprintf/libftprintf.a:
		$(MAKE) -C ./srcs/libftprintf

./srcs/get_next_line/get_next_line.a:
		$(MAKE) -C ./srcs/get_next_line

clean :
		$(MAKE) -C ./srcs/libftprintf $@
		$(MAKE) -C ./srcs/get_next_line $@
		$(RM) $(OBJS)
		$(RM) $(OBJS_BONUS)

fclean :	clean
	$(MAKE) -C ./srcs/libftprintf $@
	$(MAKE) -C ./srcs/get_next_line $@
	$(RM) $(NAME)

re :		fclean all

.PHONY :	all bonus clean fclean re
