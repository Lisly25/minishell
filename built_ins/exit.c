/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:23:17 by fshields          #+#    #+#             */
/*   Updated: 2024/03/18 12:28:31 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_valid(char *status)
{
	if (*status == '-')
		status ++;
	while (*status)
	{
		if (!ft_isdigit(*status))
			return (0);
		status ++;
	}
	return (1);
}

void	ft_exit(char *status, t_data *data)
{
	int		code;

	
	if (!status)
		ft_message_and_exit(data, 0);
	if (!check_valid(status))
	{
		ft_putstr_fd("minishell 🐢: exit: ", 2);
		ft_putstr_fd(status, 2);
		return (ft_putstr_fd(" numeric argument required\n", 2));
	}
	code = ft_atoi(status);
	ft_message_and_exit(data, code);
}
