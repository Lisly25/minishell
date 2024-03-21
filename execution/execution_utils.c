/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:19:46 by fshields          #+#    #+#             */
/*   Updated: 2024/03/21 11:26:26 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_path(t_comm *cmd, char **env_s, t_data *data)
{
	char	*path;
	char	**command;
	int		exit_code;

	command = cmd->san_command;
	if (command[0][0] == '/')
		path = find_absolute_path(command[0], data);
	else if (ft_strchr(command[0], '/') != NULL && command[0][0] != '/')
		path = find_relative_path(command[0], data);
	else
		path = find_path_from_path_env(command[0], env_s, data);
	if (path == NULL)
	{
		exit_code = data->exit_code;
		ft_free_t_data_struct(data);
		exit(exit_code);
	}
	return (path);
}

int	detect_built_in(char *command)
{
	if (command == NULL)
		return (0);
	if (ft_strncmp("echo", command, 4) == 0 && ft_strlen(command) == 4)
		return (1);
	if (ft_strncmp("cd", command, 2) == 0 && ft_strlen(command) == 2)
		return (2);
	if (ft_strncmp("pwd", command, 3) == 0 && ft_strlen(command) == 3)
		return (3);
	if (ft_strncmp("export", command, 6) == 0 && ft_strlen(command) == 6)
		return (4);
	if (ft_strncmp("unset", command, 5) == 0 && ft_strlen(command) == 5)
		return (5);
	if (ft_strncmp("env", command, 3) == 0 && ft_strlen(command) == 3)
		return (6);
	if (ft_strncmp("exit", command, 4) == 0 && ft_strlen(command) == 4)
		return (7);
	return (0);
}

int	run_built_in(char *arg, int code, t_data *data, int i)
{
	t_env	**env;

	env = &data->env;
	if (code == 1)
		return (ft_echo(arg));
	else if (code == 2)
		return (ft_cd(arg, env));
	else if (code == 3)
		return (ft_print_pwd());
	else if (code == 4)
		return (ft_export(arg, env));
	else if (code == 5)
		return (ft_unset(arg, env));
	else if (code == 6)
		return (ft_env(*env));
	else if (code == 7)
		ft_exit(arg, data, i);
	return (1);
}

void	wait_for_children(t_data *data)
{
	int		i;
	int		child_status;

	i = 0;
	while (i < data->comm_count)
	{
		if (waitpid(data->comms[i]->child_id, &child_status, 0) == -1)
		{
			ft_error_message("wait error", NULL);
			ft_free_t_data_struct(data);
			exit(1);
		}
		data->exit_code = child_status;
		while (data->exit_code > 255)
			data->exit_code -= 255;
		i++;
	}
}
