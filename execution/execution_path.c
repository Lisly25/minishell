/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:41:21 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/13 11:46:56 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_path_from_path_env(char *cmd, char **env_s)
{
	char	*full_path;
	char	**path_env_array;
	int		i;

	i = 0;
	path_env_array = get_path_env_array(env_s, cmd);
	if (path_env_array == NULL)
		return (NULL);
	while (path_env_array[i] != NULL)
	{
		full_path = ft_three_strs_join(path_env_array[i], "/", cmd);
		if (full_path == NULL)
		{
			ft_putendl_fd("minishell 🐢: malloc error", 2);
			return (NULL);
		}
		if (check_access_to_command(full_path) == 0)
		{
			if (check_if_cmd_is_directory(full_path, cmd) == 1)
			{
				free(full_path);
				ft_free_2d_array(path_env_array);
				return (NULL);
			}
			ft_free_2d_array(path_env_array);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_putstr_fd("minishell 🐢: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": No such file or directory", 2);
	ft_free_2d_array(path_env_array);
	return (NULL);
}

char	*find_absolute_path(char *cmd)//we might want to malloc this path, so then we can error handle it the same way after an execve way as everything else
{
	char	*result;

	if (check_access_to_command(cmd) == 0)
	{
		if (check_if_cmd_is_directory(cmd, cmd) == 1)
			return (NULL);
		result = ft_strdup(cmd);
		if (result == NULL)
		{
			ft_putendl_fd("minishell 🐢: malloc error", 2);
			return (NULL);
		}
		return (result);
	}
	ft_putstr_fd("minishell 🐢: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": No such file or directory", 2);
	return (NULL);
}

char	*find_relative_path(char *cmd)
{
	char	*cwd;
	char	buffer[9999];//we can't use the function pathconf() to get the size of the max path, so what else can we do?
	char	*full_path;

	cwd = getcwd(buffer, 9999);
	if (cwd == NULL)
	{
		perror("minishell 🐢: ");
		return (NULL);
	}
	full_path = ft_three_strs_join(cwd, "/", cmd);
	if (full_path == NULL)
	{
		ft_putendl_fd("minishell 🐢: malloc error", 2);
		return (NULL);
	}
	if (check_access_to_command(cmd) == 0)
	{
		if (check_if_cmd_is_directory(cmd, cmd) == 1)
		{
			free(full_path);
			return (NULL);
		}
		return (full_path);
	}
	ft_putstr_fd("minishell 🐢: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": No such file or directory", 2);
	free(full_path);
	return (NULL);
}
