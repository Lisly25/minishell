/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:23:17 by fshields          #+#    #+#             */
/*   Updated: 2024/03/20 16:17:04 by fshields         ###   ########.fr       */
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

void	ft_exit(char *status, t_data *data)
{
	int		code;

	
	if (!status)
		ft_message_and_exit(data, 0);
	if (!check_valid(status) || overflow(status))
	{
		ft_putstr_fd("minishell 🐢: exit: ", 2);
		ft_putstr_fd(status, 2);
		return (ft_putstr_fd(": numeric argument required\n", 2));
	}
	code = ft_atoi(status);
	ft_message_and_exit(data, code);
}
