/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:17:50 by fshields          #+#    #+#             */
/*   Updated: 2024/03/15 15:18:19 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*static t_comm	**dumb_parser(char *input)
{
	int		comm_no;
	int		i;
	t_comm	**comm_arr;

	comm_no = 1;
	i = 0;
	comm_arr = (t_comm **) malloc(sizeof(t_comm *) * (comm_no + 1));
	while (i < comm_no)
	{
		comm_arr[i] = (t_comm *) malloc(sizeof(t_comm));
		comm_arr[i]->command = ft_split(input, ' ');
		comm_arr[i]->input = NULL;
		comm_arr[i]->output = NULL;
		i ++;
	}
	comm_arr[i] = NULL;
	return (comm_arr);
}*/

/*int	main(int argc, char *argv[], char *env[])
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
		data->comms = dumb_parser(line);
		execute(data);
		free(line);
		free_comm(data);
	}
	printf("🐢💨 exiting\n");
	free_env_list(&(data->env));
	free(data);
	return (0);
}*/
