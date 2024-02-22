/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:44:07 by skorbai           #+#    #+#             */
/*   Updated: 2023/10/31 11:46:03 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	char_c;
	unsigned char	*buffer;
	size_t			i;

	char_c = c;
	buffer = b;
	i = 0;
	while (len > i)
	{
		buffer[i] = char_c;
		i++;
	}
	return (b);
}
