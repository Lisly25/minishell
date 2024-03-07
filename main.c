/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:34:59 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/07 17:01:49 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_code = 0;

// static void	display_structs(t_data *data)
// {
// 	t_comm *comms;
// 	int	i;
// 	int	j;

// 	comms = *(data->comms);
// 	i = 0;
// 	j = 0;
// 	while (i < data->comm_count)
// 	{
// 		while(comms[i].command[j])
// 		{
// 			printf("%s san len:%i\n", comms[i].command[j], get_san_len(comms[i].command[j], data->env));
// 			j ++;
// 		}
// 		j = 0;
// 		i ++;
// 	}
// }

int	main(int argc, char *argv[], char *env[])
{
	char	*line;
	t_data	*data;
	int		parse_status;

	init_signals();
	data = init_data(env);
	while (argc != 0 && argv != NULL)
	{
		line = readline("minishell 🐢: ");
		if (line == NULL)
		{
			rl_clear_history();
			break ;//should this not just be continue?
		}
		add_history(line);
		parse_status = parser_main(line, data);
		if (parse_status == MALLOC_ERROR)
			ft_message_and_exit(data, 1);
		else if (parse_status == SYNTAX_ERROR)
			exit_code = SYNTAX_ERROR;
		else
		{
			display_structs(data);
			execute(data);
		}
		free_comm(data);
	}
	ft_message_and_exit(data, 0);
}
