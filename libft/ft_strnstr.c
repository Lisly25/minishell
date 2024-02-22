/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:17:27 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/05 10:29:38 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_all_of_needle(char *h_stack, const char *n, size_t len)
{
	size_t	i;

	i = 0;
	while (h_stack[i] == n[i] && n[i] != '\0' && h_stack && len != 0)
	{
		i++;
		len--;
	}
	if (i == ft_strlen(n))
		return (1);
	else
		return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*result;

	result = (char *)haystack;
	if (needle[0] == '\0')
		return (result);
	while (*result != '\0' && len != 0)
	{
		if (*result == needle[0])
		{
			if (is_all_of_needle(result, needle, len) == 1)
				return (result);
		}
		result++;
		len--;
	}
	return (NULL);
}
