/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sanitiser_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:21:43 by fshields          #+#    #+#             */
/*   Updated: 2024/03/12 16:27:17 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	env_len(char *str, t_env *env)
{
	int		len;
	char	*substr;
	int		rtn;

	rtn = 0;
	len = 0;
	while (ft_isprint(str[len]) > 0 && str[len] != ' ' && \
		str[len] != 34 && str[len] != 39)
		len ++;
	len -- ;
	if (len == 0)
		return (1);
	substr = ft_substr(str, 1, len);
	while (env)
	{
		if (ft_strncmp(substr, env->name, INT_MAX) == 0)
			rtn = ft_strlen(env->value);
		env = env->next;
	}
	free(substr);
	return (rtn);
}

static void	handle_q(char ch, int *d, int *s, int *len)
{
	if (!*d && !*s)
	{
		*d = (ch == 34);
		*s = (ch == 39);
	}
	else if (*s || *d)
	{
		*len += (*d && ch == 39) + (*s && ch == 34);
		*d -= (*d && ch == 34);
		*s -= (*s && ch == 39);
	}
}

char	*expand_env_san(char *str, t_env *env)
{
	int		len;
	char	*substr;
	char	*rtn;

	rtn = NULL;
	len = 0;
	while (ft_isprint(str[len]) > 0 && str[len] != ' ' && \
		str[len] != 34 && str[len] != 39)
		len ++;
	len -- ;
	if (len == 0)
		return (ft_strdup("$"));
	substr = ft_substr(str, 1, len);
	while (env)
	{
		if (ft_strncmp(substr, env->name, INT_MAX) == 0)
			rtn = ft_strdup(env->value);
		env = env->next;
	}
	free(substr);
	return (rtn);
}

int	get_san_len(char *str, t_env *env)
{
	int	d;
	int	s;
	int	len;

	d = 0;
	s = 0;
	len = 0;
	while (*str)
	{
		if (*str == '$' && !s)
		{
			str ++;
			len += env_len((str - 1),  env);
			while (*str && *str != ' ' && *str != 34 && *str != 39)
				str ++;
			str --;
		}
		else if (*str != 34 && *str != 39)
			len ++;
		else if (*str == 34 || *str == 39)
			handle_q(*str, &d, &s, &len);
		str ++;
	}
	return (len);
}
