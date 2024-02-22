/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_uint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:31:50 by skorbai           #+#    #+#             */
/*   Updated: 2023/12/15 12:22:18 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	unsigned int	get_num_size(unsigned int n)
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

static	char	*itoa_putnbr(unsigned int n, char *result)
{
	unsigned int	remainder;
	int				i;

	remainder = 0;
	i = 0;
	while (n > 0)
	{
		remainder = n % 10;
		result[i++] = remainder + '0';
		n = (n / 10);
	}
	result[i] = '\0';
	return (result);
}

static char	*uint_itoa(unsigned int n)
{
	char	*str_num;
	int		digits;

	digits = get_num_size(n);
	str_num = malloc(digits + 1);
	if (str_num == NULL)
		return (NULL);
	if (n == 0)
	{
		str_num[0] = '0';
		str_num[1] = '\0';
		return (str_num);
	}
	str_num = itoa_putnbr(n, str_num);
	return (str_num);
}

int	printf_uint(unsigned int num)
{
	int		len;
	char	*num_str;
	int		i;

	len = 0;
	i = 0;
	num_str = uint_itoa(num);
	if (num_str == NULL)
		return (-1);
	while (num_str[i] != '\0')
		i++;
	len = printf_putstr_backwards(num_str, (i - 1));
	free (num_str);
	return (len);
}
