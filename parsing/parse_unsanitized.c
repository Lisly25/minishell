/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_unsanitized.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:59:25 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/04 16:34:01 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_unsanitized_array(char *str, t_data *data)
{
	int		status;
	char	**split_cmds;
	int		i;

	i = 0;
	status = 0;
	data->unsanit_comms = (t_unsanit_comm *)malloc(sizeof(t_unsanit_comm)\
	 * data->comm_count);
	if (data->unsanit_comms == NULL)
		return (MALLOC_ERROR);
	split_cmds = pipe_split(str);
	while (split_cmds[i] != NULL)
	{
		status = get_input_unsanit(split_cmds[i], &data->unsanit_comms[i]);
		if (status != 0)
			break ;//we should have a specific function for this that frees the allocated structs
		status = get_output_sanit(split_cmds[i], &data->unsanit_comms[i]);
		if (status != 0)
			break ;
		status = get_cmd_sanit(split_cmds[i], &data->unsanit_comms[i]);
		if (status != 0)
			break ;
		i++;
	}
	ft_free_2d_array(split_cmds);
	return (status);
}
