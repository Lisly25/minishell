/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hexadecimals.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:08:47 by skorbai           #+#    #+#             */
/*   Updated: 2023/12/15 12:22:00 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_hex_digits(unsigned int num)
{
	int	digits;

	digits = 0;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		num = num / 16;
		digits++;
	}
	return (digits);
}

static char	*convert_to_hex(unsigned int num, char *hex_form, int hex_case)
{
	int	i;
	int	temp;

	i = 0;
	temp = 0;
	if (num == 0)
		hex_form[i++] = '0';
	while (num != 0)
	{
		temp = num % 16;
		if (temp < 10)
			temp = temp + 48;
		else
			temp = temp + hex_case;
		hex_form[i++] = temp;
		num = num / 16;
	}
	hex_form[i] = '\0';
	return (hex_form);
}

int	printf_hex(unsigned int num, int hex_case)
{
	int		len;
	char	*hex_form;
	int		digits;

	len = 0;
	digits = get_hex_digits(num);
	hex_form = malloc(digits + 3);
	if (hex_form == NULL)
		return (-1);
	hex_form = convert_to_hex(num, hex_form, hex_case);
	len = printf_putstr_backwards(hex_form, (digits - 1));
	free (hex_form);
	return (len);
}
