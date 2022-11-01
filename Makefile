NAME		= pipex

SRCS		= srcs/main.c \
				srcs/pipex.c \
				srcs/errors_gestion.c \
				srcs/parsing.c \
				srcs/utils.c

SRCS_BONUS	= srcs/main_bonus.c \
				srcs/pipex.c \
				srcs/pipex_multi_pipes.c \
				srcs/pipex_heredoc.c \
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

$(NAME) :	$(OBJS) libftprintf get_next_line
			$(CC) $(OBJS) ./srcs/libftprintf/libftprintf.a ./srcs/get_next_line/get_next_line.a -o $(NAME)

bonus:		$(OBJS_BONUS) libftprintf get_next_line
			$(CC) $(OBJS_BONUS) ./srcs/libftprintf/libftprintf.a ./srcs/get_next_line/get_next_line.a -o $(NAME)

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
		$(RM) $(OBJS_BONUS)

fclean :	clean
	$(MAKE) -C ./srcs/libftprintf $@
	$(MAKE) -C ./srcs/get_next_line $@
	$(RM) $(NAME)

re :		fclean all

.PHONY :	all bonus clean fclean re libftprintf get_next_line
