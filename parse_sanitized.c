/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sanitized.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:59:25 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/01 14:58:49 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sanit_comm	*init_sanitized_array(char *str, t_command *cmds)
{
	t_sanit_comm	*result;
	char			**split_cmds;
	int				i;

	i = 0;
	result = (t_sanit_comm *)malloc(sizeof(t_sanit_comm) * cmds->comm_count);
	if (result == NULL)
		return (NULL);
	split_cmds = pipe_split(str);
	while (split_cmds[i] != NULL)
	{
		if (get_input_sanit(split_cmds[i], &result[i]) == -1)
			return (NULL);//we should have a specific function for this that frees the allocated structs
		if (get_output_sanit(split_cmds[i], &result[i]) == -1)
			return (NULL);
		if (get_cmd_sanit(split_cmds[i], &result[i]) == -1)
			return (NULL);
		i++;
	}
	ft_free_2d_array(split_cmds);
	return (result);
}
