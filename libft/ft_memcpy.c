/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:57:30 by skorbai           #+#    #+#             */
/*   Updated: 2023/11/06 16:42:50 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*buffer_s;

	i = 0;
	buffer_s = (char *) src;
	if ((n == 0) || (char *)dst == buffer_s)
		return (dst);
	while (i < n)
	{
		((char *)dst)[i] = buffer_s[i];
		i++;
	}
	return (dst);
}
