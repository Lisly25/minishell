/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_path_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:32:19 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/13 11:46:46 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_cmd_is_directory(char *path, char *cmd)
{
	int	fd;

	fd = open(path, O_DIRECTORY);
	if (fd >= 0)
	{
		ft_putstr_fd("minishell 🐢: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": is a directory", 2);
		close(fd);
		return (1);
	}
	return (0);
}

int	check_access_to_command(char *path)
{
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == 0)
			return (0);
		else
		{
			perror("minishell 🐢");//does not produce the correct format :(
			return (1);
		}
	}
	return (1);
}

char	**get_path_env_array(char **env_s, char *cmd)
{
	char	*path_env;
	char	**path_env_array;

	path_env = ft_find_str_by_prefix_in_array("PATH=", env_s);
	if (path_env == NULL)
	{
		path_env_array = (char **)malloc(sizeof(char *) * 2);
		if (path_env_array == NULL)
		{
			ft_putendl_fd("minishell 🐢: malloc error", 2);
			return (NULL);
		}
		path_env_array[0] = find_relative_path(cmd);
		if (path_env_array[0] == NULL)
		{
			free(path_env_array);
			return (NULL);
		}
		path_env_array[1] = NULL;
		return (path_env_array);//because even without the path variable, relative paths still work, and even a.out works, while normally only ./a.out would!
	}
	path_env_array = ft_split(path_env, ':');
	if (path_env_array == NULL)
	{
		ft_putendl_fd("minishell 🐢: malloc error", 2);
		return (NULL);
	}
	return (path_env_array);
}
