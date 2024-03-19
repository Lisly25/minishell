/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:19:31 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/19 15:53:23 by skorbai          ###   ########.fr       */
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
			if (c_count > 2 || (c_count == 1 && (str[i] != str[i - 1])))
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

char	*ft_strdup_only_char_c_str(char c, char *str, int i)
{
	int		j;
	int		c_count;
	char	*result;

	j = 0;
	c_count = 0;
	while (str[i] == c)
	{
		i++;
		c_count++;
	}
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

char	*ft_strdup_from_i_to_char(char c, char *str, int i)
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
	i = detect_redirect_limit(i, str, opposite_redir, c);
	result = (char *)malloc((i - j) + 1);
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

int	detect_redirect_limit(int i, char *str, char other_redir, char redir)
{
	char	quote;

	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			i++;
			while (str[i] != quote)
				i++;
		}
		if (str[i] == redir && check_if_quoted(str, i) == 0)
			break ;
		if (str[i] == other_redir && check_if_quoted(str, i) == 0)
			break ;
		if (str[i] == ' ' && check_if_quoted(str, i) == 0)
			break ;
		i++;
	}
	return (i);
}
