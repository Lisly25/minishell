/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:51:32 by fshields          #+#    #+#             */
/*   Updated: 2024/02/22 16:56:16 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(int fd, char *env[])
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (write(fd, env[i], ft_strlen(env[i])) != ft_strlen(env[i]))
			return (1);
		if (write(fd, "\n", 1) != 1)
			return (1);
		i ++;
	}
	return (0);
}
