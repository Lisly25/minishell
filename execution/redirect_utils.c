/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:34:57 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/21 11:25:08 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_last_redirect(char c, char **redirect, int j)
{
	int	i;

	i = 0;
	if (j == (ft_get_arr_size(redirect) + 2))
		return (1);
	j = j + 2;
	while (redirect[j] != NULL)
	{
		if (redirect[j][0] == c)
			return (0);
		j = j + 2;
	}
	return (1);
}

int	ft_ambi_redirect_error_msg(char *redirect)
{
	ft_putstr_fd("minishell 🐢: ", 2);
	ft_putstr_fd(redirect, 2);
	ft_putendl_fd(": ambiguous redirect", 2);
	return (1);
}
