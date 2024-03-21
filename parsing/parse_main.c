/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:08:11 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/21 14:44:11 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_empty_line(char *line)
{
	int	i;
	int	space_count;

	i = 0;
	space_count = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
			space_count++;
		i++;
	}
	if (space_count == i)
	{
		free(line);
		return (1);
	}
	return (0);
}

int	parser_main(char *input, t_data *data)
{
	int		status;

	if (ft_strlen(input) == 0)
	{
		data->comms = NULL;
		data->comm_count = 0;
		free(input);
		return (0);
	}
	data->comm_count = get_command_count(input);
	if (data->comm_count == -1)
		return (SYNTAX_ERROR);
	status = init_unsanitized_array(input, data);
	free(input);
	if (status == MALLOC_ERROR)
		return (MALLOC_ERROR);
	if (status == SYNTAX_ERROR)
		return (SYNTAX_ERROR);
	sanitiser(data);
	if (get_heredoc(data) == -1)
		return (MALLOC_ERROR);
	return (status);
}
