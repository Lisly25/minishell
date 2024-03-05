/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:51:58 by fshields          #+#    #+#             */
/*   Updated: 2024/03/05 16:31:06 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ret of 1: not built_in
//ret of -1: error
//exit: succcessul run of built-in
static int	execute_built_in(char **command, t_env **env)
{
	int	code;
	int	i;

	code = detect_built_in(command[0]);
	if (code == 0)
		return (1);
	i = 1;
	while (command[i] != NULL || i == 1)
	{
		if (run_built_in(command[i], code, env) != 0)
			return (-1);
		if (command[i] == NULL)
			break ;
		i ++;
	}
	if (code == 2)
		printf("\n");
	exit(0);
	return (0);
}

static int	exec_built_in_no_exit(t_data *data)
{
	int	code;
	int	i;
	t_unsanit_comm *command;

	command = data->unsanit_comms;
	code = detect_built_in(command->command[0]);
	i = 1;
	while (command->command[i] != NULL || i == 1)
	{
		if (run_built_in(command->command[i], code, &data->env) != 0)
			return (-1);
		if (command->command[i] == NULL)
			break ;
		i ++;
	}
	if (code == 2)
		printf("\n");
	return (0);
}

//free all memory in child processs

static int	child_process(t_unsanit_comm *command, t_env *env, char **env_s)
{
	char	*path;
	char	**arr;

	arr = env_s;
	if (execute_built_in(command->command, &env) == -1)
	{
		write(2, "execution failure\n", 18);
		exit(EXIT_FAILURE);
	}
	path = find_path(command);
	if (!path)
	{
		write(2, "command not found\n", 18);
		exit(EXIT_FAILURE);
	}
	execve(path, command->command, env_s);
	write(2, "execve failure\n", 15);
	exit(EXIT_FAILURE);
}

int	execute(t_data *data)
{
	t_unsanit_comm	*commands;
	int				i;
	int				child_status;
	
	i = 0;
	commands = data->unsanit_comms;
	if (data->comm_count == 1 && detect_built_in(commands->command[0]))
		return (exec_built_in_no_exit(data));
	while (i < data->comm_count)
	{
		commands[i].child_id = fork();
		if (commands[i].child_id == -1)
			return (write(2, "fork failure\n", 13));
		if (commands[i].child_id == 0)
			return (child_process(&commands[i], data->env, data->env_s));
		if (commands[i].child_id > 0)
			waitpid(commands[i].child_id, &child_status, 0);
		i ++;
	}
	return (0);
}
