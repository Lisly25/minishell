/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:10:35 by fshields          #+#    #+#             */
/*   Updated: 2024/02/29 16:02:28 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	unset_error(char *arg)
{
	ft_putstr_fd("minishell 🐢: unset: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (0);
}

static int	remove_var(t_env *var, t_env **env)
{
	t_env	*ptr;

	if (var == *env)
		*env = (*env)->next;
	else
	{
		ptr = *env;
		while (ptr->next != var)
			ptr = ptr->next;
		ptr->next = var->next;
	}
	free(var->name);
	free(var->value);
	free(var);
	return (0);
}

int	ft_unset(char *arg, t_env **env)
{
	t_env	*ptr;

	ptr = *env;
	if (!arg)
		return (0);
	if (ft_strchr(arg, '=') != NULL)
		return (unset_error(arg));
	while (ptr)
	{
		if (ft_strncmp(arg, ptr->name, INT_MAX) == 0)
			return (remove_var(ptr, env));
		ptr = ptr->next;
	}
	return (0);
}
