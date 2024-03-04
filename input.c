/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:17:50 by fshields          #+#    #+#             */
/*   Updated: 2024/03/04 11:47:21 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	char	*line;
	char	**split;
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
		split = ft_split(line, ' ');
		if (execute_built_in(split, 1, &data->env) != 0)
			ft_putstr_fd("not a built-in\n", 2);
		free(line);
		free(split);
	}
	printf("exiting\n");
	free_env_list(&(data->env));
	free(data);
	return (0);
}
