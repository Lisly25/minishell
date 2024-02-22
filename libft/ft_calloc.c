/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:29:14 by skorbai           #+#    #+#             */
/*   Updated: 2023/11/08 16:00:49 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

//The max size is INT_MAX squared minus 1

void	*ft_calloc(size_t count, size_t size)
{
	char			*ptr;
	int				i;
	size_t			malloc_size;
	size_t			max_size;

	i = 0;
	max_size = 4611686014132420608;
	if (count != 0 && (max_size / count) < size)
		return (NULL);
	malloc_size = count * size;
	ptr = malloc(malloc_size);
	if (ptr == NULL)
		return (NULL);
	while (malloc_size != 0)
	{
		ptr[i] = 0;
		i++;
		malloc_size--;
	}
	return (ptr);
}
