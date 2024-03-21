/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:51:58 by fshields          #+#    #+#             */
/*   Updated: 2024/03/21 15:18:42 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//ret of 1: not built_in
//ret of -1: error
//exit: succcessul run of built-in
static int	execute_built_in(t_data *data, t_comm *comm, int j)
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
		if (run_built_in(comm->san_command[i], code, data, j) != 0)
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
}

static int	built_in_loop(t_data *data, int i, int code)
{
	if (code == 1 && is_n_flag(data->comms[0]) && i == 1)
		i ++;
	if (run_built_in(data->comms[0]->san_command[i], code, data, 0) != 0)
		return (1);
	if (code == 1 && data->comms[0]->san_command[i + 1] != NULL)
		printf(" ");
	return (0);
}

static int	exec_built_in_no_exit(t_data *data)
{
	int		code;
	int		i;
	int		io[2];

	save_io(io);
	if (open_redirects_builtin(data, 0) == 1)
		return (1);
	if (redirect(data->comms[0]) == DUP2_ERROR)
		return (ft_error_msg_and_return_one("dup2 error", NULL));
	code = detect_built_in(data->comms[0]->san_command[0]);
	i = 1;
	while (data->comms[0]->san_command[i] != NULL || i == 1)
	{
		if (built_in_loop(data, i, code) == 1)
			return (1);
		if (data->comms[0]->san_command[i] == NULL || (code == 2 && i == 1))
			break ;
		i ++;
	}
	if (code == 1 && !is_n_flag(data->comms[0]))
		printf("\n");
	reset_io(io);
	return (0);
}

int	child_process(t_data *data, t_comm *comm, int i)
{
	char	*path;
	char	**env_s;

	env_s = env_to_str(data->env);
	if (comm->san_command[0] == NULL || ft_strlen(comm->san_command[0]) == 0)
	{
		if (comm->redirect == NULL && ft_strchr(comm->command[0], '$') == NULL)
			ft_msg_free_and_exit(data, 1, "command not found", NULL);
		ft_free_t_data_struct(data);
		exit(0);
	}
	if (execute_built_in(data, comm, i) == -1)
		exit(EXIT_FAILURE);
	path = find_path(comm, env_s, data);
	if (execve(path, comm->san_command, env_s) == -1)
		ft_error_message("execve error", NULL);
	free_comm(data);
	free(data);
	free(path);
	ft_free_2d_array(env_s);
	exit(EXIT_FAILURE);
}

int	execute(t_data *data)
{
	int		i;
	t_comm	**comms;

	i = 0;
	signal(SIGINT, SIG_IGN);
	comms = data->comms;
	if (data->comm_count == 0)
		return (0);
	if (data->comm_count == 1 && detect_built_in(comms[0]->san_command[0]))
	{
		data->exit_code = exec_built_in_no_exit(data);
		return (0);
	}
	init_children_and_fds(data);
	wait_for_children(data);
	handle_exit_codes(data);
	if (delete_heredocs(data) == -1)
		ft_msg_free_and_exit(data, 1, "malloc error", NULL);
	return (0);
}
