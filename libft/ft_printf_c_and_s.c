/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_c_and_s.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:19:06 by skorbai           #+#    #+#             */
/*   Updated: 2023/12/15 12:21:53 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	printf_putchar(char c)
{
	int	len;

	len = 0;
	len = write(1, &c, 1);
	return (len);
}

int	printf_arg_putstr(char *str)
{
	int	error;
	int	i;

	error = 0;
	i = 0;
	if (str == NULL)
	{
		error = write(1, "(null)", 6);
		if (error < 0)
			return (-1);
		return (6);
	}
	while (str[i] != '\0')
	{
		error = write(1, &str[i], 1);
		if (error < 0)
			return (-1);
		else
			i++;
	}
	return (i);
}
