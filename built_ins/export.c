/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:13:17 by fshields          #+#    #+#             */
/*   Updated: 2024/02/29 14:30:49 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	display_one_var(int fd, t_env *ptr)
{
	char	quote;
	
	quote = 34;	
	write(fd, "declare -x ", 11);
	write(fd, ptr->name, ft_strlen(ptr->name));
	if (!(ptr->value))
	{
		write(fd, "\n", 1);
		return ;
	}
	write(fd, "=", 1);
	write(fd, &quote, 1);
	if ((ptr->value)[0] != '\0')
		write(fd, ptr->value, ft_strlen(ptr->value));
	write(fd, &quote, 1);
	write(fd, "\n", 1);
}

static int	all_printed(t_env **env)
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

static void	reset_printed(t_env **env)
{
	t_env	*ptr;

	ptr = *env;
	while (ptr)
	{
		ptr->printed = 0;
		ptr = ptr->next;
	}
}

static void	display_vars(int fd, t_env **env)
{
	t_env	*ptr;
	t_env	*smallest;
	
	if (!*env)
		return ;
	while (!all_printed(env))
	{
		ptr = *env;
		while (ptr->printed)
			ptr ++;
		smallest = ptr;
		while (ptr)
		{
			if (ft_strncmp(ptr->name, smallest->name, INT_MAX) <= 0 && !ptr->printed)
				smallest = ptr;
			ptr = ptr->next;
		}
		display_one_var(fd, smallest);
		smallest->printed = 1;
	}
	reset_printed(env);
}

static int	add_var(char *arg, t_env **env)
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

static void	ammend_var(char *arg, t_env **env)
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

int	ft_export(int fd, char *arg, t_env **env)
{
	if (!arg)
		display_vars(fd, env);
	else if (already_in_list(arg, *env))
		ammend_var(arg, env);
	else
		add_var(arg, env);
	return (0);
}
