/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:55:05 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/13 11:34:36 by skorbai          ###   ########.fr       */
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
# define PIPE_ERROR 4
# define FORK_ERROR 5
# define DUP2_ERROR 6
# define SYNTAX_ERROR 258

typedef struct s_comm
{
	char	**redirect;
	char	**command;
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
	char		**env_s;
	t_comm		**comms;
	int			comm_count;
}				t_data;

int		parser_main(char *input, t_data *data);
int		init_unsanitized_array(char *str, t_data *data);
int		ft_parse_error(char *str);
int		ft_parse_error_too_many_chars(char c);
int		get_command_count(char *input);
int		check_for_unclosed_quotes(char *str);
int		check_if_quoted(char *str, int i);
int		ft_get_arr_size(char **arr);//this, too!
char	**ft_quoted_split(char *s);
char	*quote_split_strdup(char *str, int i, char limiter);
int		count_qsplit_frag_len(char *str, int i, char limiter);
char	**qsplit_free_and_null(char **result);
int		update_main_split_post_cpy(char *s, int i, char limiter);
char	**pipe_split(char *s);
int		add_redir_data_to_parse_struct(char *str, t_comm *cmd);
int		check_for_max_consequitve_chars_in_str(char *str);
char	*ft_strdup_only_char_c_str(char c, char *str, int i);
char	*ft_strdup_from_i_to_char(char c, char *str, int i, char limit);

//parse_sanitiser
char	*sanitise_str(char *str, t_env *env);
void	sanitiser(t_data *data);

//parse_sanitiser_utils
char	*expand_env_san(char *str, t_env *env);
int		get_san_len(char *str, t_env *env);

#endif