/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:52:43 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/01 14:08:08 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_comm_struct(void *struc, int mode)
{
	t_sanit_comm	*sanitized;
	t_unsanit_comm	*unsanitized;

	if (mode == 1)
	{
		sanitized = struc;
		free(sanitized->infile);
		free(sanitized->outfile);
		ft_free_2d_array(sanitized->command);
		free(sanitized);
	}
	else if (mode == 2)
	{
		unsanitized = struc;
		free(unsanitized->infile);
		free(unsanitized->outfile);
		ft_free_2d_array(unsanitized->command);
		free(unsanitized);
	}
	return ;
}

int	ft_fatal_parse_error_str_free(char *str, char *message, int exit_code)
{
	ft_putstr_fd("minishell 🐢: fatal error: ", 2);
	ft_putendl_fd(message, 2);
	free(str);
	exit(exit_code);
}

int	ft_fatal_parse_error_structs_free(t_command *commands, char *msg, int code)
{
	ft_putstr_fd("minishell 🐢: fatal error: ", 2);
	ft_putendl_fd(msg, 2);
	ft_free_comm_struct(commands->sanit_comms, 1);
	ft_free_comm_struct(commands->unsanit_comms, 2);
	free(commands);
	exit(code);
}

int	ft_parse_error(char *str)
{
	ft_putstr_fd("minishell 🐢: ", 2);
	ft_putendl_fd(str, 2);
	return (-1);
}

int	check_for_unclosed_quotes(char *str)
{
	int	i;
	int	single_quote_count;
	int	double_quote_count;

	i = 0;
	single_quote_count = 0;
	double_quote_count = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			single_quote_count++;
		if (str[i] == '\"')
			double_quote_count++;
		i++;
	}
	if (single_quote_count % 2 != 0)
		return (-1);
	if (double_quote_count % 2 != 0)
		return (-1);
	return (0);
}
