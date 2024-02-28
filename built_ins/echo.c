/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:49:28 by fshields          #+#    #+#             */
/*   Updated: 2024/02/28 08:48:51 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	echo_loop(int fd, char **ptr, char **env, size_t *env_len)
{
	char *str;

	str = *ptr;
	while (*str)
	{
		if (*str == '$')
		{
			*env = expand_env(str);
			if (*env)
			{
				*env_len = ft_strlen(*env);
				if (write(fd, *env, *env_len) != (ssize_t) *env_len)
					return (1);
			}
			while (ft_isprint(*str) && *str != ' ')
				str ++;
		}
		if (write(fd, str, 1) != 1)
			return (1);
		str ++;
		if ((*str == 34 || *str == 39) && *(str + 1) == '\0')
			str ++;
	}
	return (0);
}


int	ft_echo(int fd, char *str, int flag)
{
	char 	*env;
	size_t	env_len;
	
	env = NULL;
	env_len = 0;
	while (*str == ' ')
		str ++;
	if (*str == 34 || *str == 39)
		str ++;
	if (echo_loop(fd, &str, &env, &env_len) != 0)
		return (1);
	if (!flag)
	{
		if (write(fd, "\n", 1) != 1)
			return (1);
	}
	return (0);
}
