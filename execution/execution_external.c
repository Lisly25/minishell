/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_external.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:59:12 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/07 16:25:53 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_pipe(t_data *data, int i)
{
	int	status;
	int	fds[2];

	if ((data->comm_count - 1) == i)
		return (0);
	status = pipe(fds);
	if (status == -1)
		return (PIPE_ERROR);
	data->comms[i]->output_fd = fds[PIPE_WRITE_END];
	data->comms[i + 1]->input_fd = fds[PIPE_READ_END];
	return (0);
}

int	init_child(t_comm *cmd)
{
	int	status;

	status = 0;
	cmd->child_id = fork();
	if (cmd->child_id == -1)
		status = FORK_ERROR;
	return (status);
}

int	open_redirect_files(t_data *data, int i)
{
	int		status;
	t_comm	*cmd;

	cmd = data->comms[i];
	if (cmd->input != NULL)
		status = open_read(data, i);
	if (status != 0)
		return (status);
	if (cmd->output != NULL)
		status = open_write(data, i);
	if (status != 0)
		return (status);
	return (0);
}

int	redirect(t_comm *cmd)
{
	int	status;

	if (cmd->input_fd != 0)
	{
		status = dup2(cmd->input_fd, STDIN_FILENO);
		close(cmd->input_fd);
		if (status == -1)
			return (DUP2_ERROR);
	}
	if (cmd->output_fd != 1)
	{
		status = dup2(cmd->output_fd, STDOUT_FILENO);
		close (cmd->output_fd);
		if (status == -1)
			return (DUP2_ERROR);
	}
	return (0);
}

int	init_children_and_fds(t_data *data)
{
	int	i;

	while (i < data->comm_count)
	{
		if (init_pipe(data, i) == PIPE_ERROR)
			return (PIPE_ERROR);
		if (init_child(data->comms[i]) == FORK_ERROR)
			return (FORK_ERROR);
		if (data->comms[i]->child_id == 0)
		{
			if (open_redirect_files(data, i) == -1)
				continue ;
			if (redirect(data->comms[i]) == DUP2_ERROR)
				return (DUP2_ERROR);
			execute_child(data, i);
		}
		i++;
	}
	return (0);
}
