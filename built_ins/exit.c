/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:23:17 by fshields          #+#    #+#             */
/*   Updated: 2024/03/21 11:31:39 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_valid(char *status)
{
	if (*status == '-' || *status == '+')
		status ++;
	while (*status)
	{
		if (!ft_isdigit(*status))
			return (0);
		status ++;
	}
	return (1);
}

static int	overflow(char *status)
{
	long int	l;

	l = 0;
	while (*status)
	{
		if (l >= LONG_MAX / 10 && (l > LONG_MAX / 10 || \
		(*status - '0') > LONG_MAX % 10))
			return (1);
		l = (l * 10) + ((*status) - '0');
		status ++;
	}
	return (0);
}

void	ft_exit(char *status, t_data *data, int i)
{
	int		code;

	
	if (!status)
		ft_message_and_exit(data, 0);
	if (!check_valid(status) || overflow(status))
	{
		ft_putstr_fd("minishell 🐢: exit: ", 2);
		ft_putstr_fd(status, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		ft_free_t_data_struct(data);
		exit(255);
	}
	if (data->comms[i]->san_command[2] != NULL)
		return (ft_putstr_fd("minishell 🐢: exit: too many arguments\n", 2));
	code = ft_atoi(status);
	ft_message_and_exit(data, code);
}
