/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:14:43 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/07 17:16:41 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_files(char **filenames, int j, int is_after_error)
{
	int	i;

	i = 0;
	while (i < j)
	{
		close(filenames[i + 1]);
		i = i + 2;
	}
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
			break ;
		j = j + 2;
	}
	close_files(input, j);
	if (data->comms[i]->input_fd == -1)
		return (-1);
	return (0);
}

int	open_write(t_data *data, int i)
{
	int		j;
	char	**output;

	j = 0;
	output = data->comms[i]->output;
	if (i == (data->comm_count - 1) && output == NULL)//should move this check for an edge case to a helper function to save lines
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
			break ;
		j = j + 2;
	}
	close_files(output, j);
	if (data->comms[i]->output_fd == -1)
		return (-1);
	return (0);
}
