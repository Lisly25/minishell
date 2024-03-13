/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sanitiser_utils_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:06:42 by fshields          #+#    #+#             */
/*   Updated: 2024/03/13 12:07:38 by fshields         ###   ########.fr       */
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
		(*san_str) ++;
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