/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:44:07 by skorbai           #+#    #+#             */
/*   Updated: 2023/10/31 11:46:20 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*buffer;
	size_t			i;

	buffer = s;
	i = 0;
	while (n > i)
	{
		buffer[i] = '\0';
		i++;
	}
}
