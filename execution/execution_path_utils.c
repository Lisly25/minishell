/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_path_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:32:19 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/22 10:28:54 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_if_cmd_is_directory(char *path, char *cmd)
{
	int	fd;

	fd = open(path, O_DIRECTORY);
	if (fd >= 0)
	{
		ft_error_message("is a directory", cmd);
		close(fd);
		return (1);
	}
	return (0);
}

int	check_access_to_command(char *path, char *cmd, t_data *data)
{
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == 0)
		{
			if (check_if_cmd_is_directory(path, cmd) == 0)
				return (0);
			data->exit_code = 126;
			return (126);
		}
		else
		{
			ft_error_message("Permission denied", cmd);
			data->exit_code = 126;
			return (126);
		}
	}
	data->exit_code = 127;
	return (127);
}

char	**get_path_env_array(char **env_s, char *cmd, t_data *data)
{
	char	*path_env;
	char	**path_env_array;

	path_env = ft_find_str_by_prefix_in_array("PATH=", env_s);
	if (path_env == NULL)
	{
		path_env_array = (char **)malloc(sizeof(char *) * 2);
		if (path_env_array == NULL)
			return (ft_error_message_and_return_null("malloc error", NULL));
		path_env_array[0] = find_relative_path(cmd, data);
		if (path_env_array[0] == NULL)
		{
			free(path_env_array);
			return (NULL);
		}
		path_env_array[1] = NULL;
		return (path_env_array);
	}
	path_env_array = ft_split(path_env, ':');
	if (path_env_array == NULL)
		return (ft_error_message_and_return_null("malloc error", NULL));
	return (path_env_array);
}
