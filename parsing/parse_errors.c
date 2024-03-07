/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:52:43 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/07 10:55:11 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
