/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 11:48:11 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/20 11:52:07 by skorbai          ###   ########.fr       */
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

	i = 0;
	while (i < data->comm_count)
	{
		if (data->comms == NULL)
			return ;
		while (i < data->comm_count)
		{
			if (data->comms[i] != NULL)
			{
				ft_free_2d_array(data->comms[i]->redirect);
				ft_free_2d_array(data->comms[i]->command);
				ft_free_2d_array(data->comms[i]->san_command);
				free(data->comms[i]);
			}
			i++;
		}
	}
	free(data->comms);
	data->comms = NULL;
}

int	ft_error_msg_and_return_one(char *msg, char *target)
{
	ft_putstr_fd("minishell 🐢: ", 2);
	if (target != NULL)
	{
		ft_putstr_fd(target, 2);
		ft_putstr_fd(": ", 2);
		free(target);
	}
	ft_putendl_fd(msg, 2);
	return (1);
}
