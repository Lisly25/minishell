/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 08:27:53 by fshields          #+#    #+#             */
/*   Updated: 2024/03/22 14:30:57 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ctl_c(int sig)
{
	if (sig == SIGINT)
	{
		printf("\33[2K\rminishell 🐢:\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ctl_c_heredoc(int sig)
{
	if (sig == SIGINT)
		g_sig = SIGINT;
	close(STDIN_FILENO);
}

void	reset_signals(void)
{
	signal(SIGINT, ctl_c);
	signal(SIGQUIT, SIG_IGN);
}

void	default_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
