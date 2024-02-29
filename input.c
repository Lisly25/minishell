/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:17:50 by fshields          #+#    #+#             */
/*   Updated: 2024/02/28 11:10:06 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_built_in(char *line, t_data *data)
{
	if (ft_strncmp(line, "exit", 4) == 0 && ft_strlen(line) == 4)
	{
		ft_exit(0);
		return (0);
	}
	if (ft_strncmp(line, "exit ", 5) == 0)
	{
		ft_exit(ft_atoi(line + 5));
		return (0);
	}
	if (ft_strncmp(line, "cd", 2) == 0)
		return (ft_cd(line + 3, data->env));
	if (ft_strncmp(line, "env", 3) == 0)
		return (ft_env(1, data->env));
	if (ft_strncmp(line, "pwd", 3) == 0)
		return (ft_print_pwd(1));
	else if (ft_strncmp(line, "echo", 4) == 0)
		return (ft_echo(1, (line + 4)));
	return (1);
}


int	main(int argc, char *argv[], char *env[])
{
	char	*line;
	t_data	*data;
	
	init_signals();
	argc += 0;
	argv += 0;
	data = init_data(env);
	if (data->env == NULL)
		printf("env is NULL\n");
	while (1)
	{
		line = readline("minishell 🐢: ");
		if (line == NULL)
		{
			rl_clear_history();
			break ;
		}
		add_history(line);
		if (exec_built_in(line, data) != 0)
		{
			free(line);
			return (write(2, "built-in error\n", 15));
		}
		free(line);
	}
	printf("exiting\n");
	free_env_list(data->env);
	free(data);
	return (0);
}
