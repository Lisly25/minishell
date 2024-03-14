/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 08:35:42 by fshields          #+#    #+#             */
/*   Updated: 2024/03/14 16:25:06 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_env(char *str)
{
	size_t	len;
	char	*ret;
	char	*var;
	
	len = 0;
	while (ft_isprint(str[len]) > 0 && str[len] != ' ')
		len ++;
	len --;
	var = ft_substr(str, 1, len);
	if (!var)
		return (NULL);
	ret = getenv(var);
	free(var);
	return (ret);
}

void	free_env_list(t_env **env_list)
{
	t_env	*temp;
	
	while (*env_list)
	{
		temp = (*env_list)->next;
		free((*env_list)->name);
		free((*env_list)->value);
		free(*env_list);
		*env_list = temp;
	}
}

int	already_in_list(char *arg, t_env *env)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = arg;
	while (ptr[i] != '=' && ptr[i] != '\0')
		i ++;
	while (env)
	{
		if (ft_strncmp(env->name, arg, i) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

void	update_dir(char dir, char *value, t_env **env)
{
	t_env	*ptr;

	ptr = *env;
	if (dir == 'o')
	{
		while (ft_strncmp("OLDPWD", ptr->name, 6) != 0)
			ptr = ptr->next;
		free(ptr->value);
		ptr->value = ft_strdup(value);
	}
	else if (dir == 'p')
	{
		while (ft_strncmp("PWD", ptr->name, 3) != 0)
			ptr = ptr->next;
		free(ptr->value);
		ptr->value = ft_strdup(value);
	}
}
