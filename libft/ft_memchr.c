/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:32:57 by skorbai           #+#    #+#             */
/*   Updated: 2023/11/03 16:00:38 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*buffer;

	buffer = (unsigned char *) s;
	while (n > 0)
	{
		if (*buffer == (unsigned char) c)
		{
			return (buffer);
		}
		buffer++;
		n--;
	}
	return (NULL);
}
