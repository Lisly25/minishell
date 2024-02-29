NAME	=	minishell
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
SRCS	=	init.c \
			input.c \
			signals.c \
			builtin_utils.c \
			built_ins/cd.c \
			built_ins/echo.c \
			built_ins/env.c \
			built_ins/exit.c \
			built_ins/pwd.c \
			built_ins/export.c \
			built_ins/export_utils.c \
			parse_split.c \
			parse_split_utils.c
OBJS	=	$(SRCS:.c=.o)
HEADER	=	minishell.h
RL_PATH	=	~/.brew/opt/readline/lib
LIBFT	=	libft/libft.a
FSAN	=	-g -fsanitize=address -static-libsan

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

san:		
				@$(CC) $(CFLAGS) $(FSAN) $(SRCS) $(LIBFT) -lreadline -L $(RL_PATH) -o san

clean:
				@rm -f $(OBJS)
				@make clean -C ./libft

fclean:		clean
				@rm -f $(NAME)

re:			fclean all

tidymake:	
				@make fclean
				@make all
				@make clean

.PHONY:		all clean fclean re tidymake san