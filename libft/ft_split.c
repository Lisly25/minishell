/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:41:17 by skorbai           #+#    #+#             */
/*   Updated: 2023/11/21 11:40:08 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_frags(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (s[i] != '\0' && s[i] == c)
		i++;
	if (i == (int)ft_strlen(s))
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0' && i != 0)
			count++;
		i++;
	}
	return (count);
}

static int	count_frag_len(char const *s, int i, char c)
{
	int	len;

	len = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		i++;
		len++;
	}
	return (len);
}

static char	*split_strdup(char const *s, char c, int j)
{
	char	*copy;
	char	*buffer;
	int		i;

	i = 0;
	buffer = (char *) s;
	copy = malloc(count_frag_len(s, j, c) + 1);
	if (copy == NULL)
		return (NULL);
	while (buffer[j] != '\0' && buffer[j] != c)
	{
		copy[i] = buffer[j];
		i++;
		j++;
	}
	copy[i] = '\0';
	return (copy);
}

static char	**free_and_null(char **result)
{
	int	i;

	i = 0;
	while (result[i] != NULL)
		free(result[i++]);
	free(result);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = malloc((sizeof(char *)) * (count_frags(s, c) + 1));
	if (result == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			result[j] = split_strdup(s, c, i);
			if (result[j] == NULL)
				return (free_and_null(result));
			j++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		if (s[i] == c && s[i] != '\0')
			i++;
	}
	result[j] = NULL;
	return (result);
}
