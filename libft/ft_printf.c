/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:57:49 by skorbai           #+#    #+#             */
/*   Updated: 2024/01/22 11:02:40 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_arg(va_list args, char type)
{
	int		len;

	if (type == '%')
		len = write(1, &type, 1);
	if (type == 'c')
		len = printf_putchar(va_arg(args, int));
	if (type == 's')
		len = printf_arg_putstr(va_arg(args, char *));
	if (type == 'p')
		len = printf_void(va_arg(args, uintptr_t));
	if (type == 'd' || type == 'i')
		len = printf_putnbr(va_arg(args, int));
	if (type == 'X')
		len = printf_hex((va_arg(args, unsigned int)), 55);
	if (type == 'x')
		len = printf_hex((va_arg(args, unsigned int)), 87);
	if (type == 'u')
		len = printf_uint(va_arg(args, unsigned int));
	if (type != '%' && type != 'c' && type != 's' && type != 'p' && type != 'd' \
	&& type != 'X' && type != 'x' && type != 'u' && type != 'i')
		len = printf_putchar(type);
	return (len);
}

static int	printf_format_putchar(char c)
{
	int	len;

	len = 0;
	if (c != '%')
		len = write(1, &c, 1);
	return (len);
}

static int	print_all(va_list *args, char *str)
{
	int		len;
	int		len_all;
	int		i;

	i = 0;
	len = 0;
	len_all = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%' && str[i + 1] != '\0')
		{
			len = print_arg(*args, str[++i]);
			i++;
		}
		else
			len = printf_format_putchar(str[i++]);
		if (len < 0)
			return (-1);
		len_all = len_all + len;
	}
	return (len_all);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		pr_len;

	pr_len = 0;
	va_start(args, str);
	pr_len = print_all(&args, (char *) str);
	va_end(args);
	return (pr_len);
}
