/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:51:32 by fshields          #+#    #+#             */
/*   Updated: 2024/03/05 16:21:55 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_env *env)
{
	while (env)
	{
		if (env->value && env->value != '\0')
			printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
	return (0);
}
