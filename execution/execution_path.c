/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:41:21 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/15 15:00:35 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*evaluate_cmd_access_status(char *path, int cmd_access_status)
{
	if (cmd_access_status == 0)
		return (path);
	free(path);
	return (NULL);
}

char	*find_path_from_path_env(char *cmd, char **env_s)
{
	char	*full_path;
	char	**path_env_array;
	int		i;
	int		cmd_access_status;

	i = 0;
	path_env_array = get_path_env_array(env_s, cmd);
	if (path_env_array == NULL)
		return (NULL);
	while (path_env_array[i] != NULL)
	{
		full_path = ft_three_strs_join(path_env_array[i], "/", cmd);
		if (full_path == NULL)
			return (ft_error_message_and_return_null("malloc error", NULL));
		cmd_access_status = check_access_to_command(full_path, cmd);
		if (cmd_access_status == 0 || cmd_access_status == 1)
			ft_free_2d_array(path_env_array);
		if (cmd_access_status == 0 || cmd_access_status == 1)
			return (evaluate_cmd_access_status(full_path, cmd_access_status));
		free(full_path);
		i++;
	}
	ft_error_message("command not found", cmd);
	ft_free_2d_array(path_env_array);
	return (NULL);
}

char	*find_absolute_path(char *cmd)
{
	char	*result;

	if (check_access_to_command(cmd, cmd) == 0)
	{
		result = ft_strdup(cmd);
		if (result == NULL)
			return (ft_error_message_and_return_null("malloc error", NULL));
		return (result);
	}
	ft_error_message("No such file or directory", cmd);
	return (NULL);
}

char	*find_relative_path(char *cmd)
{
	char	*cwd;
	char	buffer[9999];//we can't use the function pathconf() to get the size of the max path, so what else can we do?
	char	*full_path;
	int		cmd_access_status;

	cwd = getcwd(buffer, 9999);
	if (cwd == NULL)
		return (ft_error_message_and_return_null("getcwd error", NULL));
	full_path = ft_three_strs_join(cwd, "/", cmd);
	if (full_path == NULL)
		return (ft_error_message_and_return_null("malloc error", NULL));
	cmd_access_status = check_access_to_command(full_path, cmd);
	if (cmd_access_status == 0)
		return (full_path);
	else if (cmd_access_status == 2)
		ft_error_message("No such file or directory", cmd);
	free(full_path);
	return (NULL);
}
