/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:19:46 by fshields          #+#    #+#             */
/*   Updated: 2024/03/05 17:05:11 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(t_unsanit_comm *command)
{
	char	*path;

	path = ft_strjoin("/usr/bin/", command->command[0]);
	return (path);
}

int	detect_built_in(char *command)
{
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

int	run_built_in(char *arg, int code, t_env **env)
{
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
	{
		ft_exit(arg);
		return (0);
	}
	else
		return (1);
}
