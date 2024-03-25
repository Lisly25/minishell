/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 09:55:58 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/25 10:44:22 by skorbai          ###   ########.fr       */
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
	str++;
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

void	write_to_hdoc_and_free(int hdoc_fd, char *str, t_data *data)
{
	char	*env_var_value;

	while (*str != '\0')
	{
		if (*str == '$')
		{
			if (check_if_env_format(str) == 1)
			{
				ft_putchar_fd('$', hdoc_fd);
				str++;
				continue ;
			}
			str++;
			env_var_value = check_if_existing_env(str, data);
			if (env_var_value != NULL)
				ft_putstr_fd(env_var_value, hdoc_fd);
			while (check_if_env_format(str) == 0)
				str++;
			if (*str == '\0')
				break ;
		}
		else
			ft_putchar_fd(*str, hdoc_fd);
		str++;
	}
	ft_putchar_fd('\n', hdoc_fd);
}
