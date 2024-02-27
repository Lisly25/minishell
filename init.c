/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:01:56 by fshields          #+#    #+#             */
/*   Updated: 2024/02/27 11:44:24 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_to_back(t_env **list, t_env *new)
{
	t_env	*current;

	current = *list;
	if (current == NULL)
		current = new;
	while (current->next != NULL)
	{
		printf("#\n");
		current = current->next;
	}
	current->next = new;
}

static t_env	*new_node(char *name, char *value)
{
	t_env	*new_node;

	new_node = (t_env *) malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->name = name;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

static t_env	*init_env(char *env[])
{
	int		i;
	char	**env_split;
	t_env	*env_list;

	i = 0;
	env_list = NULL;
	while (env[i] != NULL)
	{
		env_split = ft_split(env[i], '=');
		add_to_back(&env_list, new_node(env_split[0], env_split[1]));
		free(env_split);
		i ++;
	}
	return (env_list);
}

t_data	*init_data(char *env[])
{
	t_data	*data;
	
	data = (t_data *) malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->env = init_env(env);
	return (data);
}
