/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:55:05 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/28 11:20:17 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "libft/libft.h"

# define MALLOC_ERROR 2
# define UNCLOSED_QUOTE_ERROR 3

typedef struct s_sanit_comm
{
	char	file_input;
	char	heredoc_input;
	char	file_output;
	char	append_file_output;
	char	*infile;
	char	*outfile;
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
	char	**command;
	pid_t	child_id;
}	t_unsanit_comm;

typedef struct s_command
{
	t_sanit_comm	*sanit_comms;
	t_unsanit_comm	*unsanit_comms;
}	t_command;

int		ft_parse_error(char *str);
int		get_command_count(char *input);
int		check_for_unclosed_quotes(char *str);
int		ft_fatal_parse_error_str_free(char *str, char *message, int exit_code);
void	ft_free_2d_array(char **arr);//move this to minishell.h later!
int		ft_free_comm_struct(void *struc, int mode);
int		ft_fatal_parse_error_structs_free(t_command *comms, char *msg, int code);

#endif
