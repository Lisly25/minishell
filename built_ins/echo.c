/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:49:28 by fshields          #+#    #+#             */
/*   Updated: 2024/03/05 15:23:23 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//handle echo $? (gives exit code of last process)

int	ft_echo(int fd, char *str)
{
	if (!str)
		return (0);
	if (ft_strncmp(str, "-n", 2) == 0 && ft_strlen(str) == 2)
		return (0);
	if (write(fd, str, ft_strlen(str)) != (ssize_t) ft_strlen(str))
		return (write(2, "echo error\n", 11));
	return (0);
}
