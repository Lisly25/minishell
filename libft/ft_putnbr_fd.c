/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 09:46:27 by skorbai           #+#    #+#             */
/*   Updated: 2023/10/30 10:37:37 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static	void	neg_putnbr_fd(int n, int fd)
{
	if (n < -9)
	{
		neg_putnbr_fd (n / 10, fd);
		neg_putnbr_fd (n % 10, fd);
	}
	if (n <= 0 && n >= -9)
	{
		n = (-n) + '0';
		write (fd, &n, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		write (fd, "-", 1);
		neg_putnbr_fd(n, fd);
		return ;
	}
	if (n > 9)
	{
		ft_putnbr_fd (n / 10, fd);
		ft_putnbr_fd (n % 10, fd);
	}
	if (n >= 0 && n <= 9)
	{
		n = n + '0';
		write (fd, &n, 1);
	}
	return ;
}
