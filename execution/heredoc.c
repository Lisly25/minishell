/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:18:02 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/25 10:21:34 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_limiter(char *limiter, char *str)
{
	size_t	i;
	int		result;

	i = 0;
	while (str[i] != '\0' && limiter[i] != '\0')
	{
		if (str[i] == limiter[i])
			i++;
		else
			break ;
	}
	if (i != ft_strlen(limiter))
		return (0);
	else if (str[i] != '\0')
		return (0);
	i--;
	result = str[i] - limiter[i];
	if (result == 0)
		return (1);
	return (0);
}

static int	read_hdoc(int i, char *limiter, t_data *data)
{
	char	*hdoc_name;
	int		hdoc;
	char	*input;
	int		io[2];

	save_io(io);
	hdoc_name = derive_heredoc_name(i);
	if (hdoc_name == NULL)
		return (-1);
	hdoc = open(hdoc_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	while (1)
	{
		input = readline("> ");
		if (input == NULL)
			return (clean_up_after_heredoc(hdoc_name, hdoc, io, NULL));
		if (is_limiter(limiter, input) == 1)
			return (clean_up_after_heredoc(hdoc_name, hdoc, io, input));
		write_to_hdoc_and_free(hdoc, input, data);
		free(input);
	}
}

static int	is_heredoc(char *str)
{
	if (ft_strlen(str) != 2)
		return (0);
	if (str[0] != '<')
		return (0);
	signal(SIGINT, ctl_c_heredoc);
	return (1);
}

int	get_heredoc(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->comm_count)
	{
		if (data->comms[i]->redirect == NULL)
		{
			i++;
			continue ;
		}
		while (data->comms[i]->redirect[j] != NULL)
		{
			if (is_heredoc(data->comms[i]->redirect[j]) == 1)
				if (read_hdoc(i, data->comms[i]->redirect[j + 1], data) == -1)
					return (-1);
			j = j + 2;
		}
		i++;
		j = 0;
	}
	return (0);
}

int	delete_heredocs(t_data *data)
{
	int		i;
	char	*hdoc_name;

	i = 0;
	while (i < data->comm_count)
	{
		hdoc_name = derive_heredoc_name(i);
		if (hdoc_name == NULL)
			return (-1);
		unlink(hdoc_name);
		free(hdoc_name);
		i++;
	}
	return (0);
}
