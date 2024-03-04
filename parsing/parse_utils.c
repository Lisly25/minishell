/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:19:31 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/01 16:49:32 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_arr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

int	check_for_max_consequitve_chars(char **arr, char c)
{
	int	i;
	int	j;
	int	result;
	int	temp_result;

	i = 0;
	j = 0;
	result = 0;
	temp_result = 0;
	while (arr[i] != NULL)
	{
		while (arr[i][j] != '\0')
		{
			while (arr[i][j] != '\0' && (arr[i][j] == c || arr[i][j] == ' '))
				temp_result++;
			if (temp_result > result)
				result = temp_result;
			temp_result = 0;
			j++;
		}
		i++;
	}
	return (result);
}
