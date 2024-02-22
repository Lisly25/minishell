/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:10:19 by skorbai           #+#    #+#             */
/*   Updated: 2023/12/15 13:32:15 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*malloc_fail_cleanup(char **leftover)
{
	if (*leftover != NULL)
	{
		free (*leftover);
		*leftover = NULL;
	}
	return (NULL);
}

char	*gnl_strjoin(char const *pref, char const *suff, ssize_t bytes)
{
	char	*result;
	int		i;
	int		j;
	int		pref_len;

	i = 0;
	j = 0;
	pref_len = 0;
	while (pref[pref_len] != '\0')
		pref_len++;
	result = malloc(pref_len + bytes + 1);
	if (result == NULL)
		return (NULL);
	while (pref[i] != '\0')
	{
		result[i] = pref[i];
		i++;
	}
	while (j < bytes)
		result[i++] = suff[j++];
	result[i] = '\0';
	return (result);
}

char	*gnl_strdup(const char *s, int bytes, int is_leftover)
{
	char	*copy;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (is_leftover == 1)
	{
		while (s[j] != '\0')
			j++;
		bytes = j;
	}
	copy = malloc(bytes + 1);
	if (copy == NULL)
		return (NULL);
	while (i < bytes)
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*newline_strdup(char *str)
{
	char	*copy;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] != '\n')
		i++;
	copy = malloc(i + 2);
	if (copy == NULL)
		return (NULL);
	while (j <= i)
	{
		copy[j] = str[j];
		j++;
	}
	copy[j] = '\0';
	return (copy);
}
