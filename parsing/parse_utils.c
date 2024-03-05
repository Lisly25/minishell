/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:19:31 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/05 18:06:49 by skorbai          ###   ########.fr       */
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

int	check_for_max_consequitve_chars(char **arr, char c)//need to re-check this: echo Hello again! > > newout2 should give a syntax error
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

/*char	*ft_char_to_str(char c, int count)
{
	char	*result;
	int		i;

	result = (char *)malloc(count + 1);
	while(i < count)
	{
		result[i] = c;
		i++;
	}
	result[i] = '\0';
	return (result);
}*/

char	*ft_strdup_only_char_c_str(char c, char *str, int i)
{
	int		j;
	int		c_count;
	char	*result;

	j = 0;
	c_count = 0;
	while (str[i] == c)
		c_count++;
	result = (char *)malloc(c_count + 1);
	if (result == NULL)
		return (NULL);
	while (j < c_count)
	{
		result[j] = c;
		j++;
	}
	result[j] = '\0';
	return (result);
}

char	*ft_strdup_from_i_to_char(char c, char *str, int i, char limit)
{
	int		j;
	int		k;
	char	*result;

	j = i;
	k = 0;
	while (str[i] != c && (str[i] != limit || (check_if_quote_enclosed(str, i == 0))))
		i++;
	result = (char *)malloc(i + 1);
	if (result == NULL)
		return (NULL);
	while (j < i)
	{
		result[k] = str[j];
		k++;
		j++;
	}
	result[k] = '\0';
	return (result);
}
