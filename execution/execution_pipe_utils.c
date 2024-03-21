/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipe_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:36:32 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/20 16:02:45 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clean_up_unused_pipes(t_data *data, int i)
{
	if (data->comm_count == 1)
		return ;
	if ((data->comm_count - 1) == i)
		return ;
	close (data->comms[i + 1]->input_fd);
}
