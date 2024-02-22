/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:49:28 by fshields          #+#    #+#             */
/*   Updated: 2024/02/22 16:56:14 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(int fd, char *str, int flag)
{
	if (write(fd, str, ft_strlen(str)) != ft_strlen(str))
		return (1);
	if (flag)
		return (0);
	if (write(fd, "\n", 1) != 1)
		return (1);
	return (0);
}
