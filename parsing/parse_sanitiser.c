/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sanitiser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:17:27 by fshields          #+#    #+#             */
/*   Updated: 2024/03/13 14:40:42 by fshields         ###   ########.fr       */
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

static void	fill_str(char *str, char **san_str, int *d, int *s, t_data *data)
{
	char	*ptr;
	char	*temp;

	ptr = *san_str;
	while (*str)
	{
		if (ft_strncmp(str, "$?", 2) == 0 && !*s)
			handle_question(&str, &ptr, data->exit_code);
		else if (*str == '$' && !*s)
		{
			temp = expand_env_san(str, data->env);
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

char	*sanitise_str(char *str, t_data *data)
{
	int		len;
	int		d;
	int		s;
	char	*san_str;

	len = get_san_len(str, data);
	d = 0;
	s = 0;
	san_str = (char *) malloc((len + 1) * sizeof(char));
	if (!san_str)
		return (NULL);
	fill_str(str, &san_str, &d, &s, data);
	return (san_str);
}

void	sanitiser(t_data *data)
{
	int	i;
	int	j;
	int	count;
	t_comm	**comms;

	i = 0;
	j = 0;
	count = 0;
	comms = data->comms;
	while (i < data->comm_count)
	{
		while (comms[i]->command[count])
			count ++;
		comms[i]->san_command = (char **) malloc(sizeof(char *) * (count + 1));
		while (comms[i]->command[j])
		{
			comms[i]->san_command[j] = sanitise_str(comms[i]->command[j], data);
			j ++;
		}
		comms[i]->san_command[j] = NULL;
		j = 0;
		count = 0;
		i ++;
	}
}
