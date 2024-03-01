/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:12:32 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/01 11:22:18 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	check_if_quote_enclosed(char *str, int i)
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
	return (UNCLOSED_QUOTE_ERROR);//this should not happen, since we already check for it before
}

static int	check_for_or_operator(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|' && check_if_quote_enclosed(str, i) == 0)
		{
			j = i + 1;
			if (str[j] == '|')
				return (-1);
			else if (str[j] == '\0')
				return (-2);
			else if (str[j] == ' ')
			{
				while (str[j] == ' ')
					j++;
				if (str[j] == '\0')
					return (-2);
			}
		}
		i++;
	}
	return (0);
}

int	get_command_count(char *input)
{
	int	i;
	int	comm_count;
	int	or_operator_error;

	i = 0;
	comm_count = 1;
	if (check_for_unclosed_quotes(input) == -1)
		return (ft_parse_error("input error: unclosed quote"));
	or_operator_error = check_for_or_operator(input);
	if (or_operator_error == -1)
		return (ft_parse_error("input error: `||' operator not supported"));
	else if (or_operator_error == -2)
		return (ft_parse_error("input error: pipe symbol at the end of line"));
	if (check_if_first_element(input) == -1)
		return (ft_parse_error("syntax error near unexpected token `|'"));//need to revisit this, because we might need to launch a child process regardless to give the correct exit status
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

t_command	*init_command_array(char *input, int command_count)
{
	t_command	*commands;

	commands = (t_command *)malloc(sizeof(t_sanit_comm *) + \
	sizeof(t_unsanit_comm *));
	if (commands == NULL)
		ft_fatal_parse_error_str_free(input, "malloc error", 1);
	commands->comm_count = get_command_count(input);
	if (commands->comm_count == -1)
		return (NULL);
	commands->sanit_comms = init_sanitized_array(input, commands);
	if (commands->sanit_comms == NULL)
	{
		free(commands);
		ft_fatal_parse_error_str_free(input, "malloc error", 1);
	}
	commands->unsanit_comms = init_unsanitized_array();
	if (commands->unsanit_comms == NULL)
	{
		ft_free_comm_struct(commands->sanit_comms, 1);
		free(commands);
		ft_fatal_parse_error_str_free(input, "malloc error", 1);
	}
	free(input);
	return (commands);
}
//This is for testing pull requests - again