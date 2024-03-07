/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sanitiser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:17:27 by fshields          #+#    #+#             */
/*   Updated: 2024/03/07 17:01:15 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//this is all unfinished!!!

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
	substr = ft_substr(str, 1, len);
	while (env)
	{
		if (ft_strncmp(substr, env->name, INT_MAX) == 0)
		{
			rtn = ft_strlen(env->value);
			printf("env len: %i\n", rtn);
		}
		env = env->next;
	}
	free(substr);
	return (rtn);
}

static char	*expand_env2(char *str, t_env *env)
{
	int		len;
	char	*substr;
	char	*rtn;

	rtn = NULL;
	len = 0;
	while (ft_isprint(str[len]) > 0 && str[len] != ' ')
		len ++;
	len -- ;
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

// if (*str == 34)
// 		{
// 			if (!d && !s)
// 				d = 1;
// 			if (d)
// 				d = 0;
// 			if (s)
// 				len ++;
// 		}
// 		if (*str == 39)
// 		{
// 			if (!d && !s)
// 				s = 1;
// 			if (s)
// 				s = 0;
// 			if (d)
// 				len ++;
// 		}

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
		if (*str != 34 && *str != 39 && *str != '$')
			len ++;
		else if (*str == 34 || *str == 39)
			handle_q(*str, &d, &s, &len);
		else if (*str == '$')
		{
			len += env_len(str, env);
			while (*str && *str != ' ')
				str ++;
			str --;
		}
		str ++;
	}
	return (len);
}


static char	*sanitise_str(char *str)
{
	int	len;

	
}

void	sanitiser(t_data *data)
{
	
}
