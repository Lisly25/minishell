/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:41:46 by skorbai           #+#    #+#             */
/*   Updated: 2023/11/07 12:42:28 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		result;

	i = 0;
	result = 0;
	if (n == 0)
		return (result);
	while ((s1[i] != '\0' && s2[i] != '\0') && i < (n - 1))
	{
		if (s1[i] == s2[i])
			i++;
		else
			break ;
	}
	result = (unsigned char) s1[i] - (unsigned char) s2[i];
	return (result);
}
