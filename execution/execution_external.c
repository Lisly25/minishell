/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_external.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:59:12 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/18 14:54:07 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	init_pipe(t_data *data, int i)
{
	int	status;
	int	fds[2];

	if ((data->comm_count - 1) == i)
	{
		data->comms[i]->output_fd = STDOUT_FILENO;
		if (data->comm_count == 1)
			data->comms[i]->input_fd = STDIN_FILENO;
		return (0);
	}
	status = pipe(fds);
	if (status == -1)
		ft_msg_free_and_exit(data, 1, "pipe error", NULL);
	data->comms[i]->output_fd = fds[PIPE_WRITE_END];
	data->comms[i + 1]->input_fd = fds[PIPE_READ_END];
	if (i == 0)
		data->comms[i]->input_fd = STDIN_FILENO;
	return (0);
}

static int	init_child(t_comm *cmd)
{
	int	status;

	status = 0;
	cmd->child_id = fork();
	return (status);
}

int	open_redirects(t_data *data, int i)
{
	int		j;
	char	**redirect;

	j = 0;
	redirect = data->comms[i]->redirect;
	if (redirect == NULL)
		return (0);
	while (redirect[j] != NULL)
	{
		if (redirect[j][0] == '<')
		{
			data->comms[i]->input_fd = open_read(redirect, j, i, data);
			close_file(data, data->comms[i]->input_fd, j, redirect);
		}
		else
		{
			data->comms[i]->output_fd = open_write(redirect, j, data);
			close_file(data, data->comms[i]->output_fd, j, redirect);
		}
		j = j + 2;
	}
	return (0);
}

int	redirect(t_comm *cmd)
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
		init_pipe(data, i);
		if (init_child(data->comms[i]) == -1)
			ft_msg_free_and_exit(data, 1, "fork error", NULL);
		if (data->comms[i]->child_id == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			open_redirects(data, i);
			if (redirect(data->comms[i]) == DUP2_ERROR)
				ft_msg_free_and_exit(data, 1, "dup2 error", NULL);
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
