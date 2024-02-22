/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:08:20 by skorbai           #+#    #+#             */
/*   Updated: 2023/11/21 11:16:05 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	size_t				j;
	unsigned char		*buffer_d;
	const unsigned char	*buffer_s;

	i = 0;
	j = len - 1;
	buffer_s = src;
	buffer_d = dst;
	if ((dst == NULL && src == NULL) || len == 0)
		return (dst);
	while (buffer_d < buffer_s && i < len)
	{
		buffer_d[i] = buffer_s[i];
		i++;
	}
	while (buffer_s < buffer_d && len != 0)
	{
		buffer_d[j] = buffer_s[j];
		j--;
		len--;
	}
	return (dst);
}
