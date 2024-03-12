/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_three_strs_join.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:41:34 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/11 13:50:16 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_three_strs_join(char *s1, char *s2, char *s3)
{
	char	*buffer;
	char	*result;

	buffer = ft_strjoin(s1, s2);
	if (buffer == NULL)
		return (NULL);
	result = ft_strjoin(buffer, s3);
	free(buffer);
	return (result);
}
