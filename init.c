/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:01:56 by fshields          #+#    #+#             */
/*   Updated: 2024/02/29 11:56:07 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_back(t_env **list, t_env *new)
{
	t_env	*last;

	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	last = *list;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
}

t_env	*new_node(char *name, char *value)
{
	t_env	*new_node;

	new_node = (t_env *) malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->name = ft_strdup(name);
	if (value == NULL)
		new_node->value = NULL;
	else
		new_node->value = ft_strdup(value);
	new_node->order = -1;
	new_node->next = NULL;
	return (new_node);
}

int		get_list_size(t_env *list)
{
	int	size;

	size = 0;
	while (list)
	{
		size ++;
		list = list->next;
	}
	return (size);
}

static void		add_order(t_env **list)
{
	int		i;
	t_env	*ptr;
	t_env	*current_smallest;

	i = 0;
	ptr = *list;
	while (i < get_list_size(*list))
	{
		current_smallest = ptr;
		while (current_smallest->order != -1)
			current_smallest = current_smallest->next;
		while (ptr)
		{
			if (ptr->name[0] < current_smallest->name[0] && ptr->order == -1)
				current_smallest = ptr;
			ptr = ptr->next;
		}
		current_smallest->order = i++;
		ptr = *list;
	}
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
		free(env_split[0]);
		free(env_split[1]);
		free(env_split);
		i ++;
	}
	add_order(&env_list);
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
