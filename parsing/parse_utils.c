/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:19:31 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/13 11:43:25 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_get_arr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

int	check_for_max_consequitve_chars_in_str(char *str)
{
	int		i;
	int		c_count;
	char	c;

	i = 0;
	c_count = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '<' || str[i] == '>') && check_if_quoted(str, i) == 0)
		{
			c = str[i];
			while (str[i++] == c)
				c_count++;
			if (c_count > 2)
				return (ft_parse_error_too_many_chars(c));
			while (str[i] == ' ')
				i++;
			if (str[i] == '\0' || str[i] == c)
				return (ft_parse_error_too_many_chars(c));
			c_count = 0;
		}
		i++;
	}
	return (c_count);
}

char	*ft_strdup_only_char_c_str(char c, char *str, int i)
{
	int		j;
	int		c_count;
	char	*result;

	j = 0;
	c_count = 0;
	while (str[i++] == c)
		c_count++;
	result = (char *)malloc(c_count + 1);
	if (result == NULL)
		return (NULL);
	while (j < c_count)
	{
		result[j] = c;
		j++;
	}
	result[j] = '\0';
	return (result);
}

char	*ft_strdup_from_i_to_char(char c, char *str, int i, char limit)
{
	int		j;
	int		k;
	char	*result;
	char	opposite_redir;

	j = i;
	k = 0;
	if (c == '<')
		opposite_redir = '>';
	else
		opposite_redir = '<';
	while (str[i] != '\0' && str[i] != c && ((str[i] != limit && str[i] \
	!= opposite_redir) || (check_if_quoted(str, i == 0))))
		i++;
	result = (char *)malloc(i + 1);
	if (result == NULL)
		return (NULL);
	while (j < i)
	{
		result[k] = str[j];
		k++;
		j++;
	}
	result[k] = '\0';
	return (result);
}
