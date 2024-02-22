/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 09:48:01 by skorbai           #+#    #+#             */
/*   Updated: 2023/11/05 09:14:56 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strchr(const char *s, int c)
{
	char	*result;
	int		i;

	i = 0;
	result = (char *)s;
	c = (char) c;
	while (result[i] != '\0')
	{
		if (result[i] == c)
			return (result + i);
		i++;
	}
	if (result[i] == c && c == '\0')
	{
		return (result + i);
	}
	return (NULL);
}
