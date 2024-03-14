/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:08:11 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/13 15:40:51 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//this function should only be called if the input is not empty: 
//neither NULL, nor containing only whitespace

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
	sanitiser(data);
	if (get_heredoc(data) == -1)
		return (MALLOC_ERROR);
	return (status);
}

//it returns SYNTAX_ERROR on parse error - in such a case, we just need to ask for a new prompt (and free any data we might have malloced before finding the syntax error)
//if it returns MALLOC ERROR, the data struct must be freed and minishell must exit
//if it returns 0, all is good and we can move on to the execution phase