NAME		=	minishell
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
SRCS		=	main.c \
				init.c \
				init_utils.c \
				signals.c \
				execution/execution.c \
				execution/execution_internal_redirection.c \
				execution/execution_pipe_utils.c \
				execution/execution_utils.c \
				execution/execution_utils_2.c \
				execution/execution_utils_3.c \
				execution/execution_external.c \
				execution/open_redirections.c \
				execution/redirect_utils.c \
				execution/redirect_errors.c \
				execution/heredoc.c \
				execution/heredoc_utils.c \
				execution/execution_path_utils.c \
				execution/execution_path.c \
				execution/handle_exit_codes.c \
				builtin_utils.c \
				built_ins/cd.c \
				built_ins/echo.c \
				built_ins/env.c \
				built_ins/exit.c \
				built_ins/pwd.c \
				built_ins/unset.c \
				built_ins/export.c \
				built_ins/export_utils.c \
				errors.c \
				errors_2.c \
				parsing/parse_errors.c \
				parsing/parse_init.c \
				parsing/parse_main.c \
				parsing/parse_redirection.c \
				parsing/parse_split_pipes.c \
				parsing/parse_split.c \
				parsing/parse_split_utils.c \
				parsing/parse_unsanitized.c \
				parsing/parse_utils_syntax.c \
				parsing/parse_utils.c \
				parsing/parse_sanitiser.c \
				parsing/parse_sanitiser_utils.c \
				parsing/parse_sanitiser_utils_2.c \
				parsing/vector.c
OBJS		=	$(SRCS:.c=.o)
HEADER		=	minishell.h
RL_PATH		=	~/.brew/opt/readline/lib
LIBFT_DIR	=	libft
LIBFT_H		=	$(LIBFT_DIR)/libft.h
LIBFT		=	$(LIBFT_DIR)/libft.a
FSAN		=	-g -fsanitize=address -static-libsan

all:			makelibft $(NAME)

makelibft:
					@make -C ./$(LIBFT_DIR)

$(NAME):		$(OBJS) $(LIBFT) $(HEADER) $(LIBFT_H)
					@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -L $(RL_PATH) -o $(NAME)
					@echo "🐢🐢🐢🐢🐢🐢🐢🐢🐢"
					@echo "🐢  compiled !  🐢"
					@echo "🐢🐢🐢🐢🐢🐢🐢🐢🐢"

%.o:			%.c
					@$(CC) $(CFLAGS) -c $< -o $@

san:		
					@$(CC) $(CFLAGS) $(FSAN) $(SRCS) $(LIBFT) -lreadline -L $(RL_PATH) -o san

clean:
					@rm -f $(OBJS)
					@make -C $(LIBFT_DIR) clean

fclean:			clean
					@rm -f $(NAME)
					@rm -f $(LIBFT)

re:				fclean all

tidymake:	
					@make fclean
					@make all
					@make clean

.PHONY:			all makelibft clean fclean re tidymake san