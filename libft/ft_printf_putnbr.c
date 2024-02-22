/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putnbr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:11:11 by skorbai           #+#    #+#             */
/*   Updated: 2023/12/15 12:22:06 by skorbai          ###   ########.fr       */
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
	return (result);
}

static	char	*itoa_putnbr(int n, char *result, int is_neg)
{
	int	remainder;
	int	i;
	int	base;

	remainder = 0;
	i = 0;
	base = 10;
	if (is_neg == 1)
		return (result = itoa_neg_putnbr(n, result));
	while (n > 0)
	{
		remainder = n % base;
		result[i++] = remainder + '0';
		n = (n / base);
	}
	result[i] = '\0';
	return (result);
}

static char	*printf_itoa(int n)
{
	char	*str_num;
	int		digits;
	int		is_neg;

	is_neg = 0;
	if (n < 0)
		is_neg = 1;
	digits = get_num_size(n);
	str_num = malloc(is_neg + digits + 1);
	if (str_num == NULL)
		return (NULL);
	if (n == 0)
	{
		str_num[0] = '0';
		str_num[1] = '\0';
		return (str_num);
	}
	str_num = itoa_putnbr(n, str_num, is_neg);
	return (str_num);
}

int	printf_putnbr(int num)
{
	int		len;
	char	*num_str;
	int		i;

	len = 0;
	i = 0;
	num_str = printf_itoa(num);
	if (num_str == NULL)
		return (-1);
	while (num_str[i] != '\0')
		i++;
	len = printf_putstr_backwards(num_str, (i - 1));
	free (num_str);
	return (len);
}
