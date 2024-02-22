/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:08:11 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/22 15:45:36 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//this function should only be called if the input is not empty: 
//neither NULL, nor containing only whitespace

t_command	*parser_main(char *input)
{
	int			command_count;
	t_command	*full_command;

	command_count = get_command_count(input);
	if (command_count == -1)
		return (NULL);
	full_command = init_command_array(input, command_count);
	//if (full_command == NULL)
	//	return (NULL);
}
