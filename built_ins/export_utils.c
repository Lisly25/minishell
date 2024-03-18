/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:58:00 by fshields          #+#    #+#             */
/*   Updated: 2024/03/15 14:56:57 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	display_vars(t_env **env)
{
	t_env	*ptr;
	t_env	*smallest;
	
	if (!*env)
		return ;
	while (!all_printed(env))
	{
		ptr = *env;
		while (ptr->printed)
			ptr = ptr->next;
		smallest = ptr;
		while (ptr)
		{
			if (ft_strncmp(ptr->name, smallest->name, INT_MAX) <= 0 && !ptr->printed)
				smallest = ptr;
			ptr = ptr->next;
		}
		if (smallest->value == NULL)
			printf("declare -x %s\n", smallest->name);
		else
			printf("declare -x %s=\"%s\"\n", smallest->name, smallest->value);
		smallest->printed = 1;
	}
	reset_printed(env);
}

void	ammend_var(char *arg, t_env **env)
{
	t_env	*ptr;
	char	*value;
	char	*name;

	value = ft_strchr(arg, '=');
	if (!value)
		return ;
	value ++;
	*(value - 1) = '\0';
	ptr = *env;
	name = arg;
	while (ptr)
	{
		if (ft_strncmp(ptr->name, name, ft_strlen(name)) == 0)
		{
			free(ptr->value);
			ptr->value = ft_strdup(value);
			return ;
		}
		ptr = ptr->next;
	}
}

int	add_var(char *arg, t_env **env)
{
	char 	*equals;
	char	*new_name;
	char	*new_value;
	t_env	*node;

	new_value = NULL;
	equals = ft_strchr(arg, '=');
	if (equals)
	{
		new_value = equals + 1;
		*equals = '\0';
	}
	new_name = arg;
	node = new_node(new_name, new_value);
	node->printed = 0;
	add_to_back(env, node);
	return (0);
}
