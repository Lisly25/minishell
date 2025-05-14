/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_unsanitized.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:59:25 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/21 14:52:19 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		data->comms[i] = (t_comm *)ft_calloc(1, sizeof(t_comm));
		if (data->comms[i] == NULL)
			return (MALLOC_ERROR);
		data->comms[i]->input_fd = STDIN_FILENO;
		data->comms[i]->output_fd = STDOUT_FILENO;
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

static int	get_redirect_unsanit(char *str, t_comm *cmd)
{
	int	result;

	if (ft_strchr(str, '<') == NULL && ft_strchr(str, '>') == NULL)
	{
		cmd->redirect = NULL;
		return (0);
	}
	if (check_for_max_consequitve_chars_in_str(str) == SYNTAX_ERROR)
	{
		cmd->redirect = NULL;
		cmd->command = NULL;
		cmd->san_command = NULL;
		return (SYNTAX_ERROR);
	}
	result = add_redir_data_to_parse_struct(str, cmd);
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
		status = get_redirect_unsanit(split_cmds[i], data->comms[i]);
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
