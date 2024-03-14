/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 08:27:53 by fshields          #+#    #+#             */
/*   Updated: 2024/03/14 15:34:55 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctl_c(int sig)
{
	if (sig == SIGINT)
	{
		printf("\33[2K\rminishell 🐢:\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ctl_c_exe(int sig)
{
	if (sig == SIGINT)
		printf("\n");
}


void	init_signals(void)
{
	signal(SIGINT, ctl_c);
	signal(SIGQUIT, SIG_IGN);
}
