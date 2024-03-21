/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:13:17 by fshields          #+#    #+#             */
/*   Updated: 2024/03/21 15:23:59 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	all_printed(t_env **env)
{
	t_env	*ptr;

	ptr = *env;
	while (ptr)
	{
		if (ptr->printed == 0)
			return (0);
		ptr = ptr->next;
	}
	return (1);
}

void	reset_printed(t_env **env)
{
	t_env	*ptr;

	ptr = *env;
	while (ptr)
	{
		ptr->printed = 0;
		ptr = ptr->next;
	}
}

int	ft_export(char *arg, t_env **env)
{
	if (*arg == '=' && ft_strlen(arg) == 1)
	{
		ft_putstr_fd("minishell 🐢: export: `=': not a valid identifier\n", 2);
		return (1);
	}
	if (!arg)
		display_vars(env);
	else if (already_in_list(arg, *env))
		ammend_var(arg, env);
	else
		return (add_var(arg, env));
	return (0);
}
