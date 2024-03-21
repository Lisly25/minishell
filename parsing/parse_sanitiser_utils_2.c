/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sanitiser_utils_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:06:42 by fshields          #+#    #+#             */
/*   Updated: 2024/03/21 14:47:36 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_env(char **env, char **san_str)
{
	char	*ptr;
	char	*san_str_p;

	ptr = *env;
	san_str_p = *san_str;
	if (!ptr)
		return ;
	while (*ptr)
	{
		*(san_str_p++) = *(ptr++);
		(*san_str)++;
	}
	free(*env);
}

void	handle_question(char **str, char **san_str, int exit_code)
{
	char	*code;
	char	*free_me;
	char	*ptr;

	code = ft_itoa(exit_code);
	free_me = code;
	ptr = *san_str;
	while (*code)
		*(ptr ++) = *(code ++);
	*san_str += (ft_strlen(free_me));
	(*str) += 1;
	free(free_me);
}

static void	remove_null(char **ptr)
{
	int		i;

	i = 0;
	free(ptr[i]);
	ptr[i] = ptr[i + 1];
	i ++;
	while (ptr[i])
	{
		ptr[i] = ptr[i + 1];
		i ++;
	}
}

static void	remove_all_nulls(char **san_command)
{
	int		i;
	char	**ptr;

	i = 0;
	ptr = san_command;
	while (ptr[i] != NULL)
	{
		if (ptr[i][0] == '\0')
			remove_null(&ptr[i]);
		i ++;
	}
}

void	handle_nulls(t_data *data)
{
	int		i;
	t_comm	**comms;

	i = 0;
	comms = data->comms;
	while (i < data->comm_count)
		remove_all_nulls(comms[i++]->san_command);
}
