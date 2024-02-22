/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:05:59 by skorbai           #+#    #+#             */
/*   Updated: 2023/11/20 14:36:02 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	is_c_in_s(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		else
			i++;
	}
	return (0);
}

static	int	n_trim_from_back(const char *str, const char *set)
{
	int	i;

	i = ft_strlen(str) - 1;
	while ((i != 0) && (is_c_in_s(set, str[i]) == 1))
	{
		i--;
	}
	return (i);
}

static	int	strim_strlen(const char *str, const char *set, int back_tr)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (str[i] != '\0')
	{
		while (is_c_in_s(set, str[i]) == 1 && str[i] != '\0')
			i++;
		while ((is_c_in_s(set, str[i]) == 0 && str[i] != '\0') || i <= back_tr)
		{
			i++;
			len++;
		}
	}
	return (len);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*result;
	int		i;
	int		j;
	int		back_tr;

	if (ft_strlen(set) == 0 || ft_strlen(s1) == 0)
		return (ft_strdup(s1));
	back_tr = n_trim_from_back(s1, set);
	result = malloc(strim_strlen(s1, set, back_tr) + 1);
	if (result == NULL)
		return (NULL);
	i = 0;
	j = 0;
	if (s1[i] != '\0')
	{
		while (is_c_in_s(set, s1[i]) == 1 && s1[i] != '\0')
			i++;
		while ((is_c_in_s(set, s1[i]) == 0 && s1[i] != '\0') || i <= back_tr)
		{
			result[j++] = s1[i++];
		}
	}
	result[j] = '\0';
	return (result);
}
