/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:02:32 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/29 13:52:53 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_quotes(char *str, int i)
{
	if (str[i] == '\'')
	{
		i++;
		while (str[i] != '\0' && str[i] != '\'')
			i++;
		if (i == ft_strlen(str))
			return (-1);
		else
			return (i);
	}
	else
	{
		i++;
		while (str[i] != '\0' && str[i] != '\"')
			i++;
		if (i == ft_strlen(str))
			return (-1);
		else
			return (i);
	}
}

static int	count_frags(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (s[i] != '\0' && s[i] == ' ')
		i++;
	if (i == ft_strlen(s))
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == ' ' && s[i + 1] != ' ' && s[i + 1] != '\0' && i != 0)
			count++;
		if (s[i] == '\'' || s[i] == '\"')
		{
			i = handle_quotes(s, i);
			if (i == -1)
				return (-1);
		}
		i++;
	}
	return (count);
}

static char	**init_result(char *str)
{
	char	**result;
	int		frag_count;

	frag_count = count_frags(str);
	if (frag_count == -1)
		return (NULL);//This should NOT happen, since we check for unclosed quotes when we split along the pipes
	result = (char **)malloc((sizeof(char *) * (frag_count + 1)));
	return (result);
}

static char	*quote_split_strdup(char *str, int i)
{
	char	*result;
	int		j;
	char	quote;

	j = 0;
	result = (char *)malloc(count_qsplit_frag_len(str, i) + 1);
	if (result == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			break ;
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			while (str[i] != quote)
				result[j++] = str[i++];
		}
		result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

char	**ft_quoted_split(char *s)
{
	char	**result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = init_result(s);
	if (result == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] != ' ')
		{
			result[j] = quote_split_strdup(s, i);
			if (result[j] == NULL)
				return (qsplit_free_and_null(result));
			j++;
			i = update_main_split_post_cpy(s, i);
		}
		if (s[i] == ' ' && s[i] != '\0')
			i++;
	}
	result[j] = NULL;
	return (result);
}
