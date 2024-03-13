/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_str_by_prefix_in_array.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:31:40 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/11 13:40:48 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_find_str_by_prefix_in_array(char *prefix, char **arr)
{
	size_t	prefix_len;
	int		i;
	char	*result;

	prefix_len = ft_strlen(prefix);
	i = 0;
	while (arr[i] != NULL)
	{
		if (ft_strncmp(prefix, arr[i], prefix_len) == 0)
		{
			result = arr[i];
			result = result + prefix_len;
			return (result);
		}
		i++;
	}
	return (NULL);
}
