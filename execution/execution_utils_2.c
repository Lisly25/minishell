/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:39:39 by fshields          #+#    #+#             */
/*   Updated: 2024/03/19 13:41:52 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	save_io(int io[])
{
	io[0] = dup(STDIN_FILENO);
	io[1] = dup(STDOUT_FILENO);
}

void	reset_io(int io[])
{
	dup2(io[0], STDIN_FILENO);
	close(io[0]);
	dup2(io[1], STDOUT_FILENO);
	close(io[1]);
}

static int	len_of_env_arr(t_env *env)
{
	int	len;

	len = 0;
	while (env)
	{
		len ++;
		env = env->next;
	}
	return (len);
}

static char	*to_str(t_env *env)
{
	int		len;
	char	*str;
	char	*ptr;
	
	len = ft_strlen(env->name) + ft_strlen(env->value) + 1;
	str = (char *) malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	ptr = env->name;
	while (*ptr)
		*(str++) = *(ptr++);
	*str = '=';
	str ++;
	ptr = env->value;
	while (*ptr)
		*(str++) = *(ptr++);
	*str = '\0';
	str -= len;
	return (str);
}

char	**env_to_str(t_env	*env)
{
	char	**arr;
	int		len;
	int		i;

	i = 0;
	len = len_of_env_arr(env);
	arr = (char **) malloc(sizeof(char *) * (len + 1));
	if (!arr)
		return (NULL);
	while (i < len)
	{
		arr[i] = to_str(env);
		env = env->next;
		i ++;
	}
	arr[i] = NULL;
	return (arr);
}
