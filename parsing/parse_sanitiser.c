/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sanitiser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:17:27 by fshields          #+#    #+#             */
/*   Updated: 2024/03/22 11:45:37 by fshields         ###   ########.fr       */
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
			(*san_str)++;
		}
	}
}

static void	fill_str(char *str, char **san_str, int quotes[], t_data *data)
{
	char	*ptr;
	char	*temp;

	ptr = *san_str;
	while (*str)
	{
		if (ft_strncmp(str, "$?", 2) == 0 && !quotes[1])
			handle_question(&str, &ptr, data->exit_code);
		else if (*str == '$' && !quotes[1])
		{
			temp = expand_env_san(str, data->env);
			handle_env(&temp, &ptr);
			str ++;
			while (*str && *str != ' ' && *str != 34 && \
			*str != 39 && *str != '$')
				str ++;
			str --;
		}
		else if (*str == 34 || *str == 39)
			handle_q2(*str, &(quotes[0]), &(quotes[1]), &ptr);
		else
			*(ptr++) = *str;
		str ++;
	}
	*(ptr) = '\0';
}

char	*sanitise_str(char *str, t_data *data)
{
	int		len;
	char	*san_str;
	int		quotes[2];

	len = get_san_len(str, data);
	quotes[0] = 0;
	quotes[1] = 0;
	san_str = (char *) malloc((len + 1) * sizeof(char));
	if (!san_str)
		ft_msg_free_and_exit(data, 1, "malloc error", NULL);
	fill_str(str, &san_str, quotes, data);
	return (san_str);
}

void	sanitiser(t_data *data)
{
	int		i;
	int		j;
	int		ct;
	t_comm	**comms;

	i = -1;
	j = -1;
	ct = 0;
	comms = data->comms;
	while (++i < data->comm_count)
	{
		while (comms[i]->command[ct])
			ct ++;
		comms[i]->san_command = (char **)malloc(sizeof(char *) * (ct + 1));
		if (!comms[i]->san_command)
			return (ft_msg_free_and_exit(data, 1, "malloc error", NULL));
		while (comms[i]->command[++j])
			comms[i]->san_command[j] = sanitise_str(comms[i]->command[j], data);
		comms[i]->san_command[j] = NULL;
		j = -1;
		ct = 0;
	}
	handle_nulls(data);
}
