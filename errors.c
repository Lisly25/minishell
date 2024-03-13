/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:11:46 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/13 11:44:51 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_2d_array(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL)
		return ;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

//some leaks still seem to happen after using this - revisit!

void	ft_free_t_data_struct(t_data *data)
{
	int	i;

	i = 0;
	if (data != NULL)
	{
		if (data->env != NULL)
			free_env_list(&(data->env));
		if (data->comms != NULL)
		{
			while (i < data->comm_count)
			{
				if (data->comms[i] != NULL)
				{
					ft_free_2d_array(data->comms[i]->redirect);
					ft_free_2d_array(data->comms[i]->command);
				}
				i++;
			}
			free(data->comms);
		}
		free(data);
	}
}

void	ft_message_and_exit(t_data *data, int code)
{
	printf("🐢💨 exiting\n");
	ft_free_t_data_struct(data);
	exit(code);
}
