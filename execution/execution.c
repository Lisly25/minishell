/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:51:58 by fshields          #+#    #+#             */
/*   Updated: 2024/03/15 14:25:41 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_n_flag(t_comm *command)
{
	char	*str;

	str = command->san_command[1];
	if (!str)
		return (0);
	if (ft_strncmp("-n", str, 2) == 0 && ft_strlen(str) == 2)
		return (1);
	return (0);
}

//ret of 1: not built_in
//ret of -1: error
//exit: succcessul run of built-in
static int	execute_built_in(t_data *data, t_comm *comm)
{
	int	code;
	int	i;

	code = detect_built_in(comm->san_command[0]);
	if (code == 0)
		return (1);
	i = 1;
	while (comm->san_command[i] != NULL || i == 1)
	{
		if (code == 1 && is_n_flag(comm) && i == 1)
			i ++;
		if (run_built_in(comm->san_command[i], code, &data->env) != 0)
			return (-1);
		if (comm->san_command[i] == NULL)
			break ;
		if (code == 1 && comm->san_command[i + 1] != NULL)
			printf(" ");
		i ++;
	}
	if (code == 1 && !is_n_flag(comm))
		printf("\n");
	exit(0);
	return (0);
}

static int	exec_built_in_no_exit(t_data *data)
{
	int		code;
	int		i;
	t_comm	*command;

	command = *(data->comms);
	code = detect_built_in(command->san_command[0]);
	i = 1;
	while (command->san_command[i] != NULL || i == 1)
	{
		if (code == 1 && is_n_flag(command) && i == 1)
			i ++;
		if (run_built_in(command->san_command[i], code, &data->env) != 0)
			return (-1);
		if (command->san_command[i] == NULL)
			break ;
		if (code == 1 && command->san_command[i + 1] != NULL)
			printf(" ");
		i ++;
	}
	if (code == 1 && !is_n_flag(command))
		printf("\n");
	return (0);
}

int	child_process(t_data *data, t_comm *comm)
{
	char	*path;

	signal(SIGINT, ctl_c_exe);
	if (execute_built_in(data, comm) == -1)
		exit(EXIT_FAILURE);
	path = find_path(comm, data->env_s);
	if (path == NULL)
	{
		ft_free_t_data_struct(data);
		exit(1);
	}
	if (execve(path, comm->san_command, data->env_s) == -1)
		ft_putstr_fd("execve failure\n", 2);
	free_comm(data);
	free(data);
	free(path);
	exit(EXIT_FAILURE);
}

int	execute(t_data *data)
{
	int		i;
	t_comm	**comms;
	int		exit_status;

	i = 0;
	signal(SIGINT, SIG_IGN);
	comms = data->comms;
	if (data->comm_count == 0)
		return (0);
	if (data->comm_count == 1 && detect_built_in(comms[0]->san_command[0]))
		return (exec_built_in_no_exit(data));
	exit_status = init_children_and_fds(data);
	if (exit_status != 0)
	{
		printf("%d\n", exit_status);//this is just for debugging
		exit(exit_status);
	}
	wait_for_children(data);
	handle_exit_codes(data);
	if (delete_heredocs(data) == -1)//we'll need to use malloc here, we might have to check the return value of execute() int the main function after all...
		return (MALLOC_ERROR);
	return (0);
}
