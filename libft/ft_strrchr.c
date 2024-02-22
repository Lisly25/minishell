/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 09:48:01 by skorbai           #+#    #+#             */
/*   Updated: 2023/11/21 11:25:43 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	is_c_included(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	if (c == '\0')
		return (1);
	return (0);
}

char	*ft_strrchr(const char *s, int c)
{
	char	*result;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	c = (char) c;
	result = (char *)s;
	if (is_c_included(result, c) == 1)
	{
		while (i <= ft_strlen(s))
		{
			if (result[i] == c)
				j = i;
			i++;
		}
		while (j > 0)
		{
			result++;
			j--;
		}
		return (result);
	}
	else
		return (NULL);
}
