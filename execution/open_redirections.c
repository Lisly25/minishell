/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:14:43 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/13 16:19:12 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//we'll need to modify this so that several cmds in the pipe using heredoc does not cause problems
//also, the heredocs should be created in the parent process, this really should just open it!
static int	heredoc(int i)
{
	int		fd;
	char	*hdoc_name;

	hdoc_name = ft_strjoin(".heredoc", (char)i);
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

int	open_read(char **redirect, int j, int i)
{
	int	fd;

	if (ft_strlen(redirect[j]) == 1)
		fd = open(redirect[j + 1], O_RDONLY);
	else
		fd = heredoc(i);
	return (fd);
}

int	open_write(char **redirect, int j)
{
	int	fd;

	if (ft_strlen(redirect[j]) == 1)
		fd = open(redirect[j + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd = open(redirect[j + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	return (fd);
}
