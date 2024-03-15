/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:34:59 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/15 14:23:06 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	char	*line;
	t_data	*data;
	int		parse_status;

	init_signals();
	data = init_data(env);
	while (argc != 0 && argv != NULL)
	{
		signal(SIGINT, ctl_c);
		line = readline("minishell 🐢: ");
		if (line == NULL)
		{
			rl_clear_history();
			ft_message_and_exit(data, 1);
		}
		add_history(line);
		parse_status = parser_main(line, data);
		if (parse_status == MALLOC_ERROR)
			ft_message_and_exit(data, 1);
		else if (parse_status == SYNTAX_ERROR)
			data->exit_code = SYNTAX_ERROR;
		else
		{
			if (execute(data) == MALLOC_ERROR)
				ft_message_and_exit(data, 1);
		}
		free_comm(data);
	}
	ft_message_and_exit(data, 0);
}
