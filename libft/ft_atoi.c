/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:10:02 by skorbai           #+#    #+#             */
/*   Updated: 2023/11/21 11:03:30 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

static int	str_to_num(char *str, int i, int is_neg)
{
	long	result;

	result = 0;
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		if (result >= LONG_MAX / 10 && (result > LONG_MAX / 10 || \
		(str[i] - '0') > LONG_MAX % 10))
		{
			if (is_neg == 1)
				return (0);
			if (is_neg == 0)
				return (-1);
		}
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	if (is_neg == 1)
		result = 0 - result;
	return ((int) result);
}

int	ft_atoi(const char *str)
{
	int		result;
	int		i;
	int		is_neg;

	i = 0;
	result = 0;
	is_neg = 0;
	while (str[i] != '\0' && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			is_neg = 1;
		i++;
	}
	result = str_to_num((char *)str, i, is_neg);
	return (result);
}
