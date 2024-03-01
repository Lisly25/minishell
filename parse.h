/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:55:05 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/01 16:44:26 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "libft/libft.h"

# define MALLOC_ERROR 2
# define UNCLOSED_QUOTE_ERROR 3
# define SYNTAX_ERROR 258

typedef struct s_sanit_comm
{
	char	file_input;
	char	heredoc_input;
	char	file_output;
	char	append_file_output;
	char	*infile;
	char	*outfile;
	char	*hdoc_limiter;
	char	**command;
	pid_t	child_id;
}	t_sanit_comm;

typedef struct s_unsanit_comm
{
	char	file_input;
	char	heredoc_input;
	char	file_output;
	char	append_file_output;
	char	*infile;
	char	*outfile;
	char	*hdoc_limiter;
	char	**command;
	pid_t	child_id;
}	t_unsanit_comm;

typedef struct s_command
{
	t_sanit_comm	*sanit_comms;
	t_unsanit_comm	*unsanit_comms;
	int				comm_count;
}	t_command;

int				ft_parse_error(char *str);
int				get_command_count(char *input);
int				check_for_unclosed_quotes(char *str);
int				check_if_quote_enclosed(char *str, int i);
int				ft_fatal_parse_error_str_free(char *str, char *message, int exit_code);
void			ft_free_2d_array(char **arr);//move this to minishell.h later!
int				ft_get_arr_size(char **arr);//this, too!
void			ft_free_comm_struct(void *struc, int mode);
int				ft_fatal_parse_error_structs_free(t_command *comm, char *msg, int code);
char			**ft_quoted_split(char *s);
char			*quote_split_strdup(char *str, int i, char limiter);
int				count_qsplit_frag_len(char *str, int i, char limiter);
char			**qsplit_free_and_null(char **result);
int				update_main_split_post_cpy(char *s, int i, char limiter);
char			**pipe_split(char *s);
t_sanit_comm	*init_sanitized_array(char *str, t_command *cmds);
int				check_for_max_consequitve_chars(char **arr, char c);

#endif
