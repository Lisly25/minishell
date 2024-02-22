/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:43:25 by skorbai           #+#    #+#             */
/*   Updated: 2023/11/21 11:26:40 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	int		i;
	int		substr_len;

	i = 0;
	if (s == NULL)
		return (NULL);
	substr_len = len;
	if ((ft_strlen(s) - start) < len)
		substr_len = (ft_strlen(s) - start);
	if (start > ft_strlen(s))
		substr_len = 0;
	substr = malloc(substr_len + 1);
	if (substr == NULL)
		return (NULL);
	while (start < ft_strlen(s) && s[start] != '\0' && len != 0)
	{
		substr[i++] = s[start++];
		len--;
	}
	substr[i] = '\0';
	return (substr);
}
