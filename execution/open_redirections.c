/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:14:43 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/14 16:11:37 by skorbai          ###   ########.fr       */
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
	return (fd);
}

static int	check_if_file_exists(char *filename)
{
	if (access(filename, F_OK) == 1)
		return (1);
	else
		return (0);
}

//this close_file() function is used for both commands currently. For the input, it's completely fine
//for the output, we obviously should not get the "no such file or directory" message, since we are supposed to create it
//but I'm not sure why open() would fail otherwise, or what message bash would give

void	close_file(t_data *data, int fd, int j, char **file_arr)
{
	int	is_last_redir;

	if (fd == -2)
	{
		ft_printf("minishell 🐢: malloc error");
		ft_free_t_data_struct(data);
		exit(1);
	}
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
	if (check_if_file_exists(file_arr[j + 1]) == 1)
		ft_printf("minishell 🐢: %s: Permission denied\n", file_arr[j + 1]);
	else
		ft_printf("minishell 🐢: %s: No such file or directory\n", file_arr[j + 1]);
	ft_free_t_data_struct(data);
	exit(1);
}

int	open_read(char **redirect, int j, int i, t_data *data)
{
	int		fd;
	char	*sanitized_name;

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
	return (fd);
}

int	open_write(char **redirect, int j, t_data *data)
{
	int		fd;
	char	*sanitized_name;

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
	return (fd);
}
