/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:40:42 by skorbai           #+#    #+#             */
/*   Updated: 2023/11/21 11:13:19 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	get_num_size(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static	char	*reverse_string(char *s)
{
	int		len;
	int		start;
	int		end;
	char	temp;

	len = ft_strlen(s);
	start = 0;
	end = len - 1;
	while (start < end)
	{
		temp = s[start];
		s[start] = s[end];
		s[end] = temp;
		start++;
		end--;
	}
	return (s);
}

static	char	*itoa_neg_putnbr(int n, char *result)
{
	int	remainder;
	int	i;

	i = 0;
	remainder = -(n % -10);
	result[i++] = remainder + '0';
	n = (n / -10);
	while (n > 0)
	{
		remainder = n % 10;
		result[i++] = remainder + '0';
		n = n / 10;
	}
	result[i++] = '-';
	result[i] = '\0';
	result = reverse_string(result);
	return (result);
}

static	char	*itoa_putnbr(int n, char *result, int is_neg)
{
	int	remainder;
	int	i;

	remainder = 0;
	i = 0;
	if (is_neg == 1)
	{
		result = itoa_neg_putnbr(n, result);
		return (result);
	}
	while (n > 0)
	{
		remainder = n % 10;
		result[i++] = remainder + '0';
		n = (n / 10);
	}
	result[i] = '\0';
	result = reverse_string(result);
	return (result);
}

char	*ft_itoa(int n)
{
	char	*str_num;
	int		is_neg;
	int		digits;

	is_neg = 0;
	digits = get_num_size(n);
	if (n < 0)
		is_neg = 1;
	str_num = malloc(is_neg + digits + 1);
	if (str_num == NULL)
	{
		return (NULL);
	}
	if (n == 0)
	{
		str_num[0] = '0';
		str_num[1] = '\0';
		return (str_num);
	}
	str_num = itoa_putnbr(n, str_num, is_neg);
	return (str_num);
}
