/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:34:59 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/12 16:21:01 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_code = 0;

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
			break ;//we need to do some signal magic here
		}
		add_history(line);
		parse_status = parser_main(line, data);
		if (parse_status == MALLOC_ERROR)
			ft_message_and_exit(data, 1);
		else if (parse_status == SYNTAX_ERROR)
			exit_code = SYNTAX_ERROR;
		else
			execute(data);
		free_comm(data);
	}
	ft_message_and_exit(data, 0);
}
