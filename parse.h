/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:55:05 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/21 14:30:57 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "libft/libft.h"
# include "vector.h"
# include "minishell.h"

# define PIPE_READ_END 0
# define PIPE_WRITE_END 1

# define MALLOC_ERROR 2
# define UNCLOSED_QUOTE_ERROR 3
# define DUP2_ERROR 4
# define SYNTAX_ERROR 258

typedef struct s_comm
{
	char	**redirect;
	char	**command;
	char	**san_command;
	pid_t	child_id;
	int		input_fd;
	int		output_fd;
}	t_comm;

typedef struct s_env
{
	int				printed;
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	t_env		*env;
	t_comm		**comms;
	int			comm_count;
	int			exit_code;
}				t_data;

//parse_main.c
int		parser_main(char *input, t_data *data);
int		check_if_empty_line(char *line);

//parse_errors.c
int		ft_parse_error(char *str);
int		ft_parse_error_too_many_chars(char *str, int i);
int		check_for_unclosed_quotes(char *str);

//parse_init.c
int		check_if_quoted(char *str, int i);
int		get_command_count(char *input);

//parse_redirection.c
int		add_redir_data_to_parse_struct(char *str, t_comm *cmd);

//parse_split_pipes.c
char	**pipe_split(char *s);

//parse_split_utils.c
int		count_qsplit_frag_len(char *str, int i, char limiter);
char	**qsplit_free_and_null(char **result);
int		update_main_split_post_cpy(char *s, int i, char limiter);

//parse_split.c
char	*quote_split_strdup(char *str, int i, char limiter);
char	**ft_quoted_split(char *s);

//parse_unsaitized.c
int		init_unsanitized_array(char *str, t_data *data);

//parse_utils.c
int		ft_get_arr_size(char **arr);//this, too!
char	*ft_strdup_only_char_c_str(char c, char *str, int i);
char	*ft_strdup_from_i_to_char(char c, char *str, int i);
int		detect_redirect_limit(int i, char *str, char other_redir, char redir);

//parse_sanitiser
char	*sanitise_str(char *str, t_data *data);
void	sanitiser(t_data *data);

//parse_sanitiser_utils
char	*expand_env_san(char *str, t_env *env);
int		get_san_len(char *str, t_data *data);

//parse_sanitiser_utils_2
void	handle_question(char **str, char **san_str, int exit_code);
void	handle_env(char **env, char **san_str);
void	handle_nulls(t_data *data);

//parse_utils_syntax
int		check_for_max_consequitve_chars_in_str(char *str);

#endif