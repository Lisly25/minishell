/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:34:59 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/22 13:57:08 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	char	*line;
	t_data	*data;
	int		parse_status;

	data = init_data(env);
	while (argc != 0 && argv != NULL)
	{
		reset_signals();
		line = readline("minishell 🐢: ");
		if (line == NULL)
			ft_message_and_exit(data, 0);
		add_history(line);
		if (check_if_empty_line(line) == 1)
			continue ;
		parse_status = parser_main(line, data);
		if (parse_status == MALLOC_ERROR)
			ft_message_and_exit(data, 1);
		else if (parse_status == SYNTAX_ERROR)
			data->exit_code = SYNTAX_ERROR;
		else
			execute(data);
		free_comm(data);
	}
	ft_message_and_exit(data, 0);
}
