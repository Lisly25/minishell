/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:20:23 by skorbai           #+#    #+#             */
/*   Updated: 2023/11/07 12:31:07 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		i;

	i = 0;
	if (ft_strlen(dst) >= dstsize)
		return (dstsize + ft_strlen(src));
	while (*dst != '\0')
	{
		dst++;
		i++;
	}
	while (i + 1 < dstsize && *src != '\0')
	{
		*dst = *src;
		src++;
		dst++;
		i++;
	}
	*dst = '\0';
	while (*src != '\0')
	{
		src++;
		i++;
	}
	return (i);
}
