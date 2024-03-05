/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:49:28 by fshields          #+#    #+#             */
/*   Updated: 2024/03/05 16:19:16 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//handle echo $? (gives exit code of last process)

int	ft_echo(char *str)
{
	if (!str)
		return (0);
	if (ft_strncmp(str, "-n", 2) == 0 && ft_strlen(str) == 2)
		return (0);
	printf("%s", str);
	return (0);
}
