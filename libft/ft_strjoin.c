/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:47:09 by skorbai           #+#    #+#             */
/*   Updated: 2023/11/21 11:21:06 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *pre_s, char const *suf_s)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = malloc(ft_strlen(pre_s) + ft_strlen(suf_s) + 1);
	if (result == NULL)
		return (NULL);
	while (pre_s[i] != '\0')
	{
		result[i] = pre_s[i];
		i++;
	}
	while (suf_s[j] != '\0')
	{
		result[i++] = suf_s[j++];
	}
	result[i] = '\0';
	return (result);
}
