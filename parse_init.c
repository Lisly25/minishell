/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:12:32 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/22 15:27:58 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
About pipes:

trying to start a command with | (like | echo Hello) will result in an error:

	zsh: parse error near `|'
	bash: syntax error near unexpected token `|'

trying to end a command with | (like cat file1 |) will result in input getting requested with - in ZSH:

	pipe>

	If the command gets typed in correctly, it will execute as normal pipe.
	If it is not typed correctly, it will trigger an appropriate error message, as if it were a classically structured pipe
	If enter is pressed, it will keep asking for a prompt

BASH:

similar, but only the second command will be executed
*/

/*
About quotes:

- only supposed to affect shell builtins such as echo, NOT other commands like cat!
- unclosed quotes in the shell will trigger a prompt - not sure what our minishell is supposed to do. throw a custom error?
*/

static int	check_if_first_element(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == 9 || (str[i] <= 13 && str[i] >= 10))//I do NOT check for newlines, but should I?
			i++;
		else
			break ;
	}
	if (str[i] == '|')
		return (-1);
	else
		return (0);
}

static int	check_if_quote_enclosed(char *str, int i)
{
	int	j;
	int	single_quote_count;
	int	double_quote_count;

	j = 0;
	single_quote_count = 0;
	double_quote_count = 0;
	while (j < i)
	{
		if (str[j] == '\'')
			single_quote_count++;
		if (str[j] == '\"')
			double_quote_count++;
		j++;
	}
	if (single_quote_count % 2 == 0 && double_quote_count % 2 == 0)
		return (0);
	while (str[j] != '\0')
	{
		if (str[j] == '\'' || str[j] == '\"')
			return (1);
		j++;
	}
	return (UNCLOSED_QUOTE_ERROR);
}

int	get_command_count(char *input)
{
	int	i;
	int	comm_count;

	i = 0;
	comm_count = 0;
	if (check_for_unclosed_quotes(input) == -1)
		return (ft_parse_error("input error: unclosed quote"));
	if (check_if_pipe_is_first_element(input) == -1)
		return (ft_parse_error("syntax error near unexpected token '|'"));
	while (input[i] != '\0')
	{
		if (input[i] == '|')
		{
			if (check_if_quote_enclosed(input, i) == 0)
				comm_count++;
		}
		i++;
	}
	return (comm_count);
}
