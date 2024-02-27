/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:17:50 by fshields          #+#    #+#             */
/*   Updated: 2024/02/27 11:45:49 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_built_in(char *line, char **env)
{
	if (ft_strncmp(line, "exit", 4) == 0)
	{
		free(line);
		ft_exit();
		return (0);
	}
	if (ft_strncmp(line, "cd", 2) == 0)
		return (ft_cd(line + 3));
	if (ft_strncmp(line, "env", 3) == 0)
		return (ft_env(1, env));
	if (ft_strncmp(line, "pwd", 3) == 0)
		return (ft_print_pwd(1));
	if (ft_strncmp(line, "echo -n", 7) == 0)
		return (ft_echo(1, (line + 7), 1));
	else if (ft_strncmp(line, "echo", 4) == 0)
		return (ft_echo(1, (line + 4), 0));
	return (1);
}


int	main(int arc, char *argv[], char *env[])
{
	char	*line;
	t_data	*data;
	
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
		if (exec_built_in(line, env) != 0)
		{
			free(line);
			return (write(2, "built-in error\n", 15));
		}
		free(line);
	}
	printf("exiting\n");
	return (0);
}
