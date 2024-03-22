/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:12:24 by fshields          #+#    #+#             */
/*   Updated: 2024/03/22 15:16:40 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	increase_shlvl(t_env *env)
{
	int	lvl;
	
	while (env)
	{
		if (ft_strncmp(env->name, "SHLVL", 5) == 0 \
		&& ft_strlen(env->name) == 5)
		{
			lvl = ft_atoi(env->value);
			free(env->value);
			env->value = ft_itoa(lvl + 1);
			return ;
		}
		env = env->next;
	}
}
