/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_unsanitized.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:59:25 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/07 10:25:36 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_t_comm_struct(t_data *data)
{
	int	i;

	i = 0;
	data->comms = (t_comm **)malloc(sizeof(t_comm *) * \
	data->comm_count);
	if (data->comms == NULL)
		return (MALLOC_ERROR);
	while (i < data->comm_count)
	{
		data->comms[i] = (t_comm *)malloc(sizeof(t_comm));
		if (data->comms[i] == NULL)
			return (MALLOC_ERROR);
		i++;
	}
	return (0);
}

static int	get_cmd_unsanit(char *str, t_comm *cmd)
{
	char	**cmd_array;

	cmd_array = ft_quoted_split(str);
	if (cmd_array == NULL)
		return (MALLOC_ERROR);
	cmd->command = cmd_array;
	return (0);
}

static int	get_output_unsanit(char *str, t_comm *cmd)
{
	int	result;
	int	max_consequitve_chars;

	if (ft_strchr(str, '>') == NULL)
	{
		cmd->output = NULL;
		return (0);
	}
	max_consequitve_chars = check_for_max_consequitve_chars_in_str(str, '>');
	if (max_consequitve_chars > 2)
		return (ft_parse_error("syntax error near unexpected token `>>'"));
	else if (max_consequitve_chars == -1)
		return (-1);
	result = add_redir_data_to_parse_struct(str, '>', cmd);
	return (result);
}

static int	get_input_unsanit(char *str, t_comm *cmd)
{
	int	result;
	int	max_consequitve_chars;

	if (ft_strchr(str, '<') == NULL)
	{
		cmd->input = NULL;
		return (0);
	}
	max_consequitve_chars = check_for_max_consequitve_chars_in_str(str, '<');
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
	if (init_t_comm_struct(data) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	split_cmds = pipe_split(str);
	while (split_cmds[i] != NULL)
	{
		status = get_input_unsanit(split_cmds[i], data->comms[i]);
		if (status != 0)
			break ;
		status = get_output_unsanit(split_cmds[i], data->comms[i]);
		if (status != 0)
			break ;
		status = get_cmd_unsanit(split_cmds[i], data->comms[i]);
		if (status != 0)
			break ;
		i++;
	}
	ft_free_2d_array(split_cmds);
	return (status);
}
