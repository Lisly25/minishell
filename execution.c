/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:51:58 by fshields          #+#    #+#             */
/*   Updated: 2024/03/04 12:17:44 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	detect_built_in(char *command)
{
	if (ft_strncmp("echo -n", command, 7) == 0 && ft_strlen(command) == 7)
		return (1);
	if (ft_strncmp("echo", command, 4) == 0 && ft_strlen(command) == 4)
		return (2);
	if (ft_strncmp("cd", command, 2) == 0 && ft_strlen(command) == 2)
		return (3);
	if (ft_strncmp("pwd", command, 3) == 0 && ft_strlen(command) == 3)
		return (4);
	if (ft_strncmp("export", command, 6) == 0 && ft_strlen(command) == 6)
		return (5);
	if (ft_strncmp("unset", command, 5) == 0 && ft_strlen(command) == 5)
		return (6);
	if (ft_strncmp("env", command, 3) == 0 && ft_strlen(command) == 3)
		return (7);
	if (ft_strncmp("exit", command, 4) == 0 && ft_strlen(command) == 4)
		return (8);
	return (0);
}

static int	run_built_in(char *arg, int fd, int code, t_env **env)
{
	if (code == 1 || code == 2)
		return (ft_echo(fd, arg));
	else if (code == 3)
		return (ft_cd(arg, env));
	else if (code == 4)
		return (ft_print_pwd(fd));
	else if (code == 5)
		return (ft_export(fd, arg, env));
	else if (code == 6)
		return (ft_unset(arg, env));
	else if (code == 7)
		return (ft_env(fd, *env));
	else if (code == 8)
	{
		ft_exit(arg);
		return (0);
	}
	else
		return (1);
}

//ret of 1: not built_in
//ret of -1: error
//will exit upon successful run of built-in
int	execute_built_in(char **command, int fd, t_env **env)
{
	int	code;
	int	i;

	code = detect_built_in(command[0]);
	if (code == 0)
		return (1);
	i = 1;
	while (command[i] != NULL || i == 1)
	{
		if (run_built_in(command[i], fd, code, env) != 0)
			return (-1);
		if (command[i] == NULL)
			break ;
		i ++;
	}
	if (code == 2)
		write(fd, "\n", 1);
	exit(0);
	return (0);
}
