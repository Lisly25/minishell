/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sanitiser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:17:27 by fshields          #+#    #+#             */
/*   Updated: 2024/03/12 16:26:04 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_q2(char ch, int *d, int *s, char **san_str)
{
	char	*ptr;

	ptr = *san_str;
	if (!*d && !*s)
	{
		*d = (ch == 34);
		*s = (ch == 39);
	}
	else if (*s || *d)
	{
		*s -= (*s && ch == 39);
		*d -= (*d && ch == 34);
		if ((*s && ch == 34) || (*d && ch == 39))
		{
			*ptr = ch;
			(*san_str) ++;
		}
	}
}

static void	handle_env(char **env, char **san_str)
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

static void	fill_str(char *str, char **san_str, int *d, int *s, t_env *env)
{
	char	*ptr;
	char	*temp;

	ptr = *san_str;
	while (*str)
	{
		if (*str == '$' && !*s)
		{
			temp = expand_env_san(str, env);
			handle_env(&temp, &ptr);
			while (*str && *str != ' ' && *str != 34 && *str != 39)
				str ++;
			str --;
		}
		else if (*str == 34 || *str == 39)
			handle_q2(*str, d, s, &ptr);
		else
			*(ptr++) = *str;
		str ++;
	}
	*(ptr) = '\0';
}

char	*sanitise_str(char *str, t_env *env)
{
	int		len;
	int		d;
	int		s;
	char	*san_str;

	len = get_san_len(str, env);
	d = 0;
	s = 0;
	san_str = (char *) malloc((len + 1) * sizeof(char));
	if (!san_str)
		return (NULL);
	fill_str(str, &san_str, &d, &s, env);
	return (san_str);
}

void	sanitiser(t_data *data)
{
	int		i;
	int		j;
	char	*temp;
	t_comm	*comms;

	i = 0;
	j = 0;
	comms = *(data->comms);
	while (i < data->comm_count)
	{
		while (comms[i].command[j])
		{
			temp = sanitise_str(comms[i].command[j], data->env);
			free(comms[i].command[j]);
			comms[i].command[j] = ft_strdup(temp);
			free(temp);
			j ++;
		}
		i ++;
		j = 0;
	}
}
