/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_syntax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:36:41 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/21 14:52:30 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_if_valid_redir_token(char *str, int c_count, int i)
{
	if (i == 1)
		return (0);
	if (c_count == 1)
		return (0);
	i--;
	if (str[i] == str[i - 1])
		return (0);
	ft_putchar_fd(str[i], 2);
	ft_putendl_fd(" <- Error found here?", 2);
	return (1);
}

int	check_for_max_consequitve_chars_in_str(char *str)
{
	int		i;
	int		c_count;

	i = 0;
	c_count = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '<' || str[i] == '>') && check_if_quoted(str, i) == 0)
		{
			while (str[i] == '<' || str[i] == '>')
			{
				i++;
				c_count++;
			}
			if (c_count > 2 || check_if_valid_redir_token(str, c_count, i) == 1)
				return (ft_parse_error_too_many_chars(str, i));
			while (str[i] == ' ')
				i++;
			if (str[i] == '\0' || str[i] == '<' || str[i] == '>')
				return (ft_parse_error_too_many_chars(str, i));
			c_count = 0;
		}
		i++;
	}
	return (c_count);
}
