/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:14:04 by skorbai           #+#    #+#             */
/*   Updated: 2023/11/01 15:43:42 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t			i;
	int				result;
	unsigned char	*s1;
	unsigned char	*s2;

	i = 0;
	result = 0;
	s1 = (unsigned char *) str1;
	s2 = (unsigned char *) str2;
	if (n == 0)
		return (result);
	while (i < (n - 1))
	{
		if (s1[i] == s2[i])
			i++;
		else
			break ;
	}
	result = s1[i] - s2[i];
	return (result);
}
