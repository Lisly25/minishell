/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:51:32 by fshields          #+#    #+#             */
/*   Updated: 2024/02/28 11:19:57 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(int fd, t_env *env)
{
	while (env)
	{
		if (env->value && env->value != '\0')
		{
			if (write(fd, env->name, ft_strlen(env->name)) == -1)
				return (write(2, "error displaying env\n", 21));
			if (write(fd, "=", 1) == -1)
				return (write(2, "error displaying env\n", 21));
			if (write(fd, env->value, ft_strlen(env->value)) == -1)
				return (write(2, "error displaying env\n", 21));
			if (write(fd, "\n", 1) == -1)
				return (write(2, "error displaying env\n", 21));
		}
		env = env->next;
	}
	return (0);
}
