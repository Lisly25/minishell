/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sanitized_input.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:03:12 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/28 17:26:24 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	find_redir_mid_input(char *str, t_command *commands)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (str[i] != '\0')
	{
		if (str[i] == '<')
		{
			if (i != 0 && str[--i] == '<')
			{
				commands->sanit_comms->heredoc_input = 'Y';
				commands->sanit_comms->file_input = 'N';
			}
			else
				return ;
		}
		i--;
	}
}

static void	get_input_mode_sanit(char *str, t_command *commands)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] == ' ')
		i++;
	if (str[i] == '<')
	{
		if (str[++i] == '<')
		{
			commands->sanit_comms->heredoc_input = 'Y';
			commands->sanit_comms->file_input = 'N';
		}
		else
		{
			commands->sanit_comms->heredoc_input = 'N';
			commands->sanit_comms->file_input = 'Y';
		}
	}
	else
	{
		find_redir_mid_input(str, commands);
		commands->sanit_comms->heredoc_input = 'N';
		commands->sanit_comms->file_input = 'N';
	}
}

static int	get_infile_sanit(char *str, t_command *commands)
{
	// I should flag the syntax errors at some point - where a single < is in the middle of the string for example. But where best do it???
}

void	get_input_sanit(char *str, t_command *commands)
{
	int	result;

	get_input_mode_sanit(str, commands);
	if (commands->sanit_comms->file_input == 'Y')
		result = get_infile_sanit(str, commands);
	else if (commands->sanit_comms->heredoc_input == 'Y')
		result = get_hdoc_limiter_sanit(str, commands);
	else
		return ;
}
