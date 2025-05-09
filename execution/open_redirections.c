/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:14:43 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/22 10:29:29 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	heredoc(int i)
{
	int		fd;
	char	*hdoc_name;

	hdoc_name = derive_heredoc_name(i);
	if (hdoc_name == NULL)
		return (-2);
	fd = open(hdoc_name, O_RDONLY);
	free(hdoc_name);
	return (fd);
}

int	check_if_file_exists(char *filename)
{
	if (access(filename, F_OK) == 0)
		return (1);
	else
		return (0);
}

void	close_file(t_data *data, int fd, int j, char **file_arr)
{
	int		is_last_redir;
	char	*sanitized_name;

	if (fd == -2)
		ft_msg_free_and_exit(data, 1, "malloc error", NULL);
	if (fd == -3)
	{
		ft_free_t_data_struct(data);
		exit(1);
	}
	is_last_redir = check_if_last_redirect(file_arr[j][0], file_arr, j);
	if (fd > 0 && is_last_redir == 0)
	{
		close(fd);
		return ;
	}
	if (fd > 0 && is_last_redir == 1)
		return ;
	sanitized_name = sanitise_str(file_arr[j + 1], data);
	if (sanitized_name == NULL)
		ft_msg_free_and_exit(data, 1, "malloc error", NULL);
	if (check_if_file_exists(file_arr[j + 1]) == 1)
		ft_msg_free_and_exit(data, 1, "Permission denied", sanitized_name);
	ft_msg_free_and_exit(data, 1, "No such file or directory", sanitized_name);
}

int	open_read(char **redirect, int j, int i, t_data *data)
{
	int			fd;
	int			old_fd;
	char		*sanitized_name;
	static int	count = 0;

	old_fd = data->comms[i]->input_fd;
	if (ft_strlen(redirect[j]) == 1)
	{
		if (detect_ambiguous_redirect(redirect[j + 1], data) == 1)
			return (-3);
		sanitized_name = sanitise_str(redirect[j + 1], data);
		if (sanitized_name == NULL)
			return (-2);
		fd = open(sanitized_name, O_RDONLY);
		free(sanitized_name);
	}
	else
		fd = heredoc(i);
	count++;
	if (count == 1 && old_fd != STDIN_FILENO)
		close (old_fd);
	return (fd);
}

int	open_write(char **redirect, int j, int i, t_data *data)
{
	int			fd;
	int			old_fd;
	char		*sanitized_name;
	static int	count = 0;

	old_fd = data->comms[i]->output_fd;
	if (detect_ambiguous_redirect(redirect[j + 1], data) == 1)
		return (-3);
	sanitized_name = sanitise_str(redirect[j + 1], data);
	if (sanitized_name == NULL)
		return (-2);
	if (ft_strlen(redirect[j]) == 1)
		fd = open(sanitized_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd = open(sanitized_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	free (sanitized_name);
	count++;
	if (count == 1 && old_fd != STDOUT_FILENO)
		close(old_fd);
	return (fd);
}
