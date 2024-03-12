/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_external.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:59:12 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/12 16:01:28 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	init_pipe(t_data *data, int i)
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

static int	init_child(t_comm *cmd)
{
	int	status;

	status = 0;
	cmd->child_id = fork();
	if (cmd->child_id == -1)
		status = FORK_ERROR;
	return (status);
}

//we'll need to see which order bash handles redirections in
//does it open the input files first?
//or does it do it the order they are in in the input string, regardless of input/output?
static int	open_redirect_files(t_data *data, int i)
{
	int		status;
	t_comm	*cmd;

	status = 0;
	cmd = data->comms[i];
	if (cmd->input != NULL)
	{
		status = open_read(data, i);
		if (status != 0)
			return (status);
	}
	if (cmd->input == NULL && i == 0)
	{
		//if (data->comm_count > 1)
		//	close(data->comms[i]->input_fd);
		cmd->input_fd = STDIN_FILENO;
	}
	if (cmd->output != NULL)
	{
		status = open_write(data, i);
		if (status != 0)
			return (status);
	}
	if (cmd->output == NULL && i == (data->comm_count - 1))
	{
		cmd->output_fd = STDOUT_FILENO;
	}
	return (0);
}

static int	redirect(t_comm *cmd)
{
	int	status;

	if (cmd->input_fd != STDIN_FILENO)
	{
		status = dup2(cmd->input_fd, STDIN_FILENO);
		close(cmd->input_fd);
		if (status == -1)
			return (DUP2_ERROR);
	}
	if (cmd->output_fd != STDOUT_FILENO)
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

	i = 0;
	while (i < data->comm_count)
	{
		if (init_pipe(data, i) == PIPE_ERROR)
			return (PIPE_ERROR);
		if (init_child(data->comms[i]) == FORK_ERROR)
			return (FORK_ERROR);
		if (data->comms[i]->child_id == 0)
		{
			if (open_redirect_files(data, i) == -1)
				exit(1);//need better error handling here
			if (redirect(data->comms[i]) == DUP2_ERROR)
				exit(DUP2_ERROR);//this is not okay - also need to free!
			child_process(data, data->comms[i]);
		}
		if (i == (data->comm_count - 1))
			break ;
		close(data->comms[i]->output_fd);
		if (i != 0)
			close(data->comms[i]->input_fd);
		i++;
	}
	return (0);
}
