/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:17:50 by fshields          #+#    #+#             */
/*   Updated: 2024/02/22 16:48:11 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	main(int arc, char *argv[], char *env[])
{
	char	*line;

	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("minishell 🐢: ");
		if (line == NULL)
		{
			rl_clear_history();
			break ;
		}
		add_history(line);
		if (ft_strncmp(line, "cd", 2) == 0)
			ft_cd(line + 3);
		if (ft_strncmp(line, "env", 3) == 0)
			ft_env(1, env);
		if (ft_strncmp(line, "pwd", 3) == 0)
			ft_print_pwd(1);
		if (ft_strncmp(line, "echo -n", 7) == 0)
			ft_echo(1, line, 1);
		else if (ft_strncmp(line, "echo", 4) == 0)
			ft_echo(1, line, 0);
		free(line);
	}
	printf("exiting\n");
	return (0);
}
