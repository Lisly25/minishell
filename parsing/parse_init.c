/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:12:32 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/19 10:23:52 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_if_first_element(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			i++;
		else
			break ;
	}
	if (str[i] == '|')
		return (-1);
	else
		return (0);
}

//returns 0 if char is not in quotes, 1 if it is between quotes
//will also return 0 if the character itself is a quote that is not between other quotes
int	check_if_quoted(char *str, int i)
{
	int		j;
	char	quote;

	j = 0;
	while (str[j] != '\0')
	{
		if (str[j] == '\'' || str[j] == '\"')
		{
			quote = str[j];
			j++;
			while (str[j] != quote)
				j++;
			if (j > i)
				return (1);
		}
		else if (j == i)
			return (0);
		j++;
	}
	return (0);
}

static int	check_for_or_operator(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|' && check_if_quoted(str, i) == 0)
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
		return (ft_parse_error("syntax error near unexpected token `|'"));
	while (input[i] != '\0')
	{
		if (input[i] == '|')
		{
			if (check_if_quoted(input, i) == 0)
				comm_count++;
		}
		i++;
	}
	return (comm_count);
}
