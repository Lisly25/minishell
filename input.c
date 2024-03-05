/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:17:50 by fshields          #+#    #+#             */
/*   Updated: 2024/03/05 14:04:54 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_comm(t_data * data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->comm_count)
	{
		while (data->unsanit_comms[i].command[j] != NULL)
			free(data->unsanit_comms[i].command[j++]);
		free(data->unsanit_comms[i].command);
		i ++;
		j = 0;
	}
	free(data->unsanit_comms);
	data->unsanit_comms = NULL;
}

static t_unsanit_comm *init_sample_parsed(char *input)
{
	t_unsanit_comm *command;

	command = (t_unsanit_comm *) malloc(sizeof(t_unsanit_comm));
	if (!command)
		return (NULL);
	command->command = ft_split(input, ' ');
	command->input = NULL;
	command->output = NULL;
	return (command);
}

int	main(int argc, char *argv[], char *env[])
{
	char	*line;
	t_data	*data;
	
	argc += 0;
	argv += 0;
	init_signals();
	data = init_data(env);
	while (1)
	{
		line = readline("minishell 🐢: ");
		if (line == NULL)
		{
			rl_clear_history();
			break ;
		}
		add_history(line);
		data->unsanit_comms = init_sample_parsed(line);
		execute(data);
		free(line);
		free_comm(data);
	}
	printf("🐢💨 exiting\n");
	free_env_list(&(data->env));
	free(data);
	return (0);
}
