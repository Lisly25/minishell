/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 09:55:58 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/22 15:28:22 by skorbai          ###   ########.fr       */
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

char	*sanitize_heredoc_input(char *input, t_data *data)
{
	char	*result;

	result = sanitise_str(input, data);
	free(input);
	return (result);
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

void	write_to_hdoc_and_free(int hdoc_fd, char *str)
{
	ft_putendl_fd(str, hdoc_fd);
	free(str);
}
