/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:52:43 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/13 10:54:47 by skorbai          ###   ########.fr       */
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
