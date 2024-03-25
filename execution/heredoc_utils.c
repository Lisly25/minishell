/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 09:55:58 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/25 12:09:58 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*derive_heredoc_name(int num)
{
	char	*num_str;
	char	*hdoc_name;

	num_str = ft_itoa(num);
	if (num_str == NULL)
		return (NULL);
	hdoc_name = ft_strjoin(".heredoc", num_str);
	free(num_str);
	return (hdoc_name);
}

int	clean_up_after_heredoc(char *fname, int hdoc_fd, int io[], char *input)
{
	reset_io(io);
	reset_signals();
	free(fname);
	close(hdoc_fd);
	if (input != NULL)
		free (input);
	return (0);
}

static int	check_if_env_format(char *str)
{
	if (*str == '$')
		return (1);
	else if (*str == ' ')
		return (1);
	else if (*str == '\'')
		return (1);
	else if (*str == '\"')
		return (1);
	else if (*str == '\0')
		return (1);
	return (0);
}

static char	*check_if_existing_env_hdoc(char *str, t_data *data)
{
	t_env	*env;
	int		i;
	char	*str_start;

	str_start = str;
	env = data->env;
	i = 0;
	while (env != NULL)
	{
		while (env->name[i] != '\0' && check_if_env_format(str) == 0 \
		&& env->name[i] == *str)
		{
			i++;
			str++;
		}
		if (env->name[i] == '\0' && check_if_env_format(str) == 1)
			return (env->value);
		i = 0;
		str = str_start;
		env = env->next;
	}
	return (NULL);
}

void	write_to_heredoc(int hdoc_fd, char *str, t_data *data)
{
	char	*env_var_value;

	while (*str != '\0')
	{
		if (*str == '$')
		{
			str++;
			if (check_if_env_format(str) == 1)
			{
				ft_putchar_fd('$', hdoc_fd);
				continue ;
			}
			env_var_value = check_if_existing_env_hdoc(str, data);
			if (env_var_value != NULL)
				ft_putstr_fd(env_var_value, hdoc_fd);
			while (check_if_env_format(str) == 0)
				str++;
			if (*str == '\0')
				break ;
			ft_putchar_fd(*str, hdoc_fd);
		}
		else
			ft_putchar_fd(*str, hdoc_fd);
		str++;
	}
}
