/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit_codes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:36:12 by fshields          #+#    #+#             */
/*   Updated: 2024/03/14 16:05:22 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_signal(int status)
{
	int	sig;

	sig = WTERMSIG(status);
	if (sig == SIGSEGV)
		ft_putstr_fd("Segmentation fault: 11\n", 2);
	else if (sig == SIGBUS)
		ft_putstr_fd("Bus error: 7\n", 2);
	else if (sig == SIGABRT)
		ft_putstr_fd("Sig abort: 6\n", 2);
	else if (sig == SIGTERM)
		ft_putstr_fd("Terminated: 15\n", 2);
}

void	handle_exit_codes(t_data *data)
{
	int	status;

	status = data->exit_code;
	if (WIFEXITED(status))
		return ;
	else if (status == 2)
		printf("\n");
	else if (WIFSIGNALED(status))
		print_signal(status);
}
