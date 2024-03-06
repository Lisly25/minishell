/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_unsanitized.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:59:25 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/06 10:39:37 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_cmd_sanit(char *str, t_unsanit_comm *cmd)
{
	char	**cmd_array;

	cmd_array = ft_quoted_split(str);
	if (cmd_array == NULL)
		return (MALLOC_ERROR);
	cmd->command = cmd_array;
	return (0);
}

static int	get_output_unsanit(char *str, t_unsanit_comm *cmd)
{
	int	result;
	int	max_consequitve_chars;

	max_consequitve_chars = check_for_max_consequitve_chars(str, '>');
	if (max_consequitve_chars > 2)
		return (ft_parse_error("syntax error near unexpected token `>>'"));
	else if (max_consequitve_chars == -1)
		return (-1);
	result = add_redir_data_to_parse_struct(str, '>', cmd);
	return (result);
}

static int	get_input_unsanit(char *str, t_unsanit_comm *cmd)
{
	int	result;
	int	max_consequitve_chars;

	max_consequitve_chars = check_for_max_consequitve_chars(str, '<');
	if (max_consequitve_chars > 2)
		return (ft_parse_error("syntax error near unexpected token `<<'"));
	else if (max_consequitve_chars == -1)
		return (-1);
	result = add_redir_data_to_parse_struct(str, '<', cmd);
	return (result);
}

int	init_unsanitized_array(char *str, t_data *data)
{
	int		status;
	char	**split_cmds;
	int		i;

	i = 0;
	status = 0;
	data->unsanit_comms = (t_unsanit_comm *)malloc(sizeof(t_unsanit_comm) *\
	 data->comm_count);
	if (data->unsanit_comms == NULL)
		return (MALLOC_ERROR);
	split_cmds = pipe_split(str);
	while (split_cmds[i] != NULL)
	{
		status = get_input_unsanit(split_cmds[i], &data->unsanit_comms[i]);
		if (status != 0)
			break ;//we should have a specific function for this that frees the allocated structs
		status = get_output_unsanit(split_cmds[i], &data->unsanit_comms[i]);
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
