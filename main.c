/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:34:59 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/13 16:11:47 by skorbai          ###   ########.fr       */
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
			execute(data);//we must check the return value of this for malloc errors!
		free_comm(data);
	}
	ft_message_and_exit(data, 0);
}
