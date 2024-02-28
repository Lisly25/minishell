NAME	=	minishell
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
SRCS	=	init.c \
			input.c \
			signals.c \
			utils.c \
			built_ins/cd.c \
			built_ins/echo.c \
			built_ins/env.c \
			built_ins/exit.c \
			built_ins/pwd.c
OBJS	=	$(SRCS:.c=.o)
HEADER	=	minishell.h
RL_PATH	=	~/.brew/opt/readline/lib
LIBFT	=	libft/libft.a

all:		$(NAME)

$(LIBFT):
				@make -C ./libft

$(NAME):	$(OBJS) $(LIBFT) $(HEADER)
				@$(CC) $(OBJS) $(LIBFT) -lreadline -L $(RL_PATH) -o $(NAME)
				@echo "🐢🐢🐢🐢🐢🐢🐢🐢🐢"
				@echo "🐢  compiled !  🐢"
				@echo "🐢🐢🐢🐢🐢🐢🐢🐢🐢"

%.o:		%.c
				@$(CC) $(CFLAGS) -c $< -o $@

clean:
				@rm -f $(OBJS)
				@make clean -C ./libft

fclean:		clean
				@rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re