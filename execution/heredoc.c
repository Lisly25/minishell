/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:18:02 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/13 16:10:36 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_limiter(char *limiter, char *str)
{
	int	i;
	int	result;

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

static int	read_to_heredoc(int i, char *limiter)
{
	char	*hdoc_name;
	int		hdoc;
	char	*input;

	hdoc_name = ft_strjoin(".heredoc", (char)i);
	if (hdoc_name == NULL)
		return (-1);
	hdoc = open(hdoc_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	while (1)
	{
		input = readline(">");
		if (input == NULL)
			break ;
		if (is_limiter(limiter, input) == 1)
		{
			free(input);
			break ;
		}
		ft_putstr_fd(input, hdoc);
		free(input);
	}
	close(hdoc);
}

static int	is_heredoc(char *str)
{
	if (ft_strlen(str) != 1)
		return (0);
	if (str[0] != '<')
		return (0);
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
		while (data->comms[i]->redirect[j] != NULL)
		{
			if (is_heredoc(data->comms[i]->redirect[j]) == 1)
			{
				if (read_to_heredoc(i, data->comms[i]->redirect[j + 1]) == -1)
					return (-1);
			}
			j = j + 2;
		}
		i++;
	}
}

int	delete_heredocs(t_data *data)
{
	//we'll see if we get an error message for trying to delete nonexistent files, but I don't think so
	int		i;
	char	*hdoc_name;

	i = 0;
	while (i < data->comm_count)
	{
		hdoc_name = ft_strjoin(".heredoc", (char)i);
		if (hdoc_name == NULL)
			return (-1);
		unlink(hdoc_name);
		free(hdoc_name);
		i++;
	}
	return (0);
}
