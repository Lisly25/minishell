/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:55:05 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/22 15:23:28 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "libft/libft.h"

# define MALLOC_ERROR 2
# define UNCLOSED_QUOTE_ERROR 3

typedef struct s_no_quote_comm
{
	char	file_input;
	char	heredoc_input;
	char	file_output;
	char	append_file_output;
	char	*infile;
	char	*outfile;
	char	**command;
	pid_t	child_id;
}	t_no_quote_comm;

typedef struct s_quotes_comm
{
	char	file_input;
	char	heredoc_input;
	char	file_output;
	char	append_file_output;
	char	*infile;
	char	*outfile;
	char	**command;
	pid_t	child_id;
}	t_quotes_comm;

typedef struct s_command
{
	t_no_quote_comm	**no_quote_comms;
	t_quotes_comm	**quotes_comms;
}	t_command;

int	ft_parse_error(char *str);
int	get_command_count(char *input);
int	check_for_unclosed_quotes(char *str);

#endif
