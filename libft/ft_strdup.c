/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:20:35 by skorbai           #+#    #+#             */
/*   Updated: 2023/11/07 14:29:49 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*copy;
	int		i;
	char	*buffer;

	i = 0;
	buffer = (char *) s1;
	copy = malloc(ft_strlen(s1) + 1);
	if (copy == NULL)
		return (NULL);
	while (buffer[i] != '\0')
	{
		copy[i] = buffer[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
