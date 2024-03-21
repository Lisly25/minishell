/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_internal_redirection.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:11:48 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/21 13:55:40 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	close_f_builtin(t_data *data, int fd, int j, char **file_arr)
{
	int		is_last_redir;
	char	*san_name;

	if (fd == -2)
		ft_msg_free_and_exit(data, 1, "malloc error", NULL);
	if (fd == -3)
		return (1);
	is_last_redir = check_if_last_redirect(file_arr[j][0], file_arr, j);
	if (fd > 0 && is_last_redir == 0)
	{
		close(fd);
		return (0);
	}
	if (fd > 0 && is_last_redir == 1)
		return (0);
	san_name = sanitise_str(file_arr[j + 1], data);
	if (san_name == NULL)
		ft_msg_free_and_exit(data, 1, "malloc error", NULL);
	if (check_if_file_exists(file_arr[j + 1]) == 1)
		return (ft_error_msg_and_return_one("Permission denied", san_name));
	return (ft_error_msg_and_return_one("No such file or directory", san_name));
}

int	open_redirects_builtin(t_data *data, int i)
{
	int		j;
	char	**redir;

	j = 0;
	redir = data->comms[i]->redirect;
	if (redir == NULL)
		return (0);
	while (redir[j] != NULL)
	{
		if (redir[j][0] == '<')
		{
			data->comms[i]->input_fd = open_read(redir, j, i, data);
			if (close_f_builtin(data, data->comms[i]->input_fd, j, redir) == 1)
				return (1);
		}
		else
		{
			data->comms[i]->output_fd = open_write(redir, j, i, data);
			if (close_f_builtin(data, data->comms[i]->output_fd, j, redir) == 1)
				return (1);
		}
		j = j + 2;
	}
	return (0);
}
