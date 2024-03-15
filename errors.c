/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:11:46 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/15 11:53:57 by skorbai          ###   ########.fr       */
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
					ft_free_2d_array(data->comms[i]->san_command);
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

void	ft_msg_free_and_exit(t_data *data, int code, char *msg, char *target)
{
	ft_putstr_fd("minishell 🐢: ", 2);
	if (target != NULL)
	{
		ft_putstr_fd(target, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(msg, 2);
	ft_free_t_data_struct(data);
	exit(code);
}

void	*ft_error_message_and_return_null(char *msg, char *target)
{
	ft_putstr_fd("minishell 🐢: ", 2);
	if (target != NULL)
	{
		ft_putstr_fd(target, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(msg, 2);
	return (NULL);
}
