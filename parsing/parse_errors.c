/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:52:43 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/19 15:55:57 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_parse_error(char *str)
{
	ft_putstr_fd("minishell 🐢: ", 2);
	ft_putendl_fd(str, 2);
	return (-1);
}

int	ft_parse_error_too_many_chars(char *str, int i)
{
	int	j;

	j = 0;
	ft_putstr_fd("minishell 🐢: syntax error near unexpected token `", 2);
	if (str[i] == '\0')
		ft_putstr_fd("newline", 2);
	else
	{
		i--;
		if (i > 0)
			i--;
		while (j < 2)
		{
			if (str[i] != '>' && str[i] != '<')
				break ;
			ft_putchar_fd(str[i], 2);
			j++;
			i++;
		}
	}
	ft_putendl_fd("'", 2);
	return (SYNTAX_ERROR);
}

int	check_for_unclosed_quotes(char *str)
{
	int		i;
	char	quote;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i++];
			while (str[i] != quote && str[i] != '\0')
				i++;
			if (str[i] == '\0')
				return (-1);
		}
		i++;
	}
	return (0);
}
