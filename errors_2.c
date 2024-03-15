/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 11:48:11 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/15 15:18:26 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_message(char *message, char *target)
{
	ft_putstr_fd("minishell 🐢: ", 2);
	ft_putstr_fd(target, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(message, 2);
}

void	free_comm(t_data *data)
{
	int		i;
	int		j;
	t_comm	**comms;

	comms = data->comms;
	if (!comms || !(*comms))
		return ;
	i = 0;
	j = 0;
	while (i < data->comm_count)
	{
		while (comms[i]->command[j] != NULL)
		{
			free(comms[i]->command[j]);
			free(comms[i]->san_command[j]);
			j ++;
		}
		free(comms[i]->command);
		free(comms[i]->san_command);
		free(comms[i]);
		i ++;
		j = 0;
	}
	free(comms);
	data->comms = NULL;
}
