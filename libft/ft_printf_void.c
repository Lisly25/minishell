/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_void.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:23:02 by skorbai           #+#    #+#             */
/*   Updated: 2023/12/15 12:22:24 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_hex_digits(uintptr_t num)
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

static char	*convert_to_hex(uintptr_t adress, char *hex_form)
{
	int	i;
	int	temp;

	i = 0;
	temp = 0;
	if (adress == 0)
		hex_form[i++] = '0';
	while (adress != 0)
	{
		temp = adress % 16;
		if (temp < 10)
			temp = temp + 48;
		else
			temp = temp + 87;
		hex_form[i++] = temp;
		adress = adress / 16;
	}
	hex_form[i++] = 'x';
	hex_form[i++] = '0';
	hex_form[i] = '\0';
	return (hex_form);
}

int	printf_void(uintptr_t adress)
{
	int		len;
	char	*hex_form;
	int		digits;

	len = 0;
	digits = get_hex_digits(adress);
	hex_form = malloc(digits + 3);
	if (hex_form == NULL)
		return (-1);
	hex_form = convert_to_hex(adress, hex_form);
	len = printf_putstr_backwards(hex_form, (digits + 1));
	free(hex_form);
	return (len);
}
