/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:34:57 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/13 12:41:13 by skorbai          ###   ########.fr       */
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
