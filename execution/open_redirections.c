/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:14:43 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/08 10:31:51 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_if_file_exists(char *filename)
{
	if (access(filename, F_OK) == 1)
		return (1);
	else
		return (0);
}

//this close_files() function is used for both commands currently. For the input, it's completely fine
//for the output, we obviously should not get the "no such file or directory" message, since we are supposed to create it
//but I'm not sure why open() would fail otherwise, or what message bash would give
static int	close_files(char **filenames, int j, int is_error, t_data *data)
{
	int	i;

	i = 0;
	while (i < j)
	{
		close(filenames[i + 1]);
		i = i + 2;
	}
	if (is_error == 1)
	{
		if (check_if_file_exists(filenames[j + 1]) == 1)
			ft_printf("minishell 🐢: %s: Permission denied\n", filenames[j + 1]);
		else
			ft_printf("minishell 🐢: %s: No such file or dierctory\n", filenames[j + 1]);
		ft_free_t_data_struct(data);
		exit(1);
	}
	return (0);
}

int	open_read(t_data *data, int i)
{
	int		j;
	char	**input;

	j = 0;
	input = data->comms[i]->input;
	if (i == 0 && input == NULL)
	{
		data->comms[i]->input_fd = 0;//this means, in bash, is that we are given a prompt - should we detect this case in the execute function? It does seem like in the case of multiple pipes, while the shell is waiting for the prompt, it WILL be running >sleep< later down the pipeline
		return (0);
	}
	while (input[j] != NULL)
	{
		if (ft_strlen(input[j]) == 1)
			data->comms[i]->input_fd = open(input[j + 1], O_RDONLY);
		else
			data->comms[i]->input_fd = heredoc(data->comms[i]);
		if (data->comms[i]->input_fd == -1)
			return (close_files(input, j, 1, data));
		j = j + 2;
	}
	close_files(input, j, 0, data);
	return (0);
}

int	open_write(t_data *data, int i)
{
	int		j;
	char	**output;

	j = 0;
	output = data->comms[i]->output;
	if (i == (data->comm_count - 1) && output == NULL)
	{
		data->comms[i]->output_fd = 1;
		return (0);
	}
	while (output[j] != NULL)
	{
		if (ft_strlen(output[j]) == 1)
			data->comms[i]->output_fd = open(output[j + 1], \
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else
			data->comms[i]->output_fd = open(output[j + 1], \
			O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (data->comms[i]->output_fd == -1)
			return (close_files(output, j, 1, data));
		j = j + 2;
	}
	close_files(output, j, 0, data);
	return (0);
}
