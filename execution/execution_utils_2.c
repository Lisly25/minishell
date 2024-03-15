/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:39:39 by fshields          #+#    #+#             */
/*   Updated: 2024/03/15 14:40:12 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	save_io(int io[])
{
	io[0] = dup(STDIN_FILENO);
	io[1] = dup(STDOUT_FILENO);
}

void	reset_io(int io[])
{
	dup2(io[0], STDIN_FILENO);
	close(io[0]);
	dup2(io[1], STDOUT_FILENO);
	close(io[1]);
}
