/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 09:55:58 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/22 11:49:10 by skorbai          ###   ########.fr       */
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

int	clean_up_after_reading_heredoc(char *hdoc_name, int hdoc_fd)
{
	free(hdoc_name);
	close(hdoc_fd);
	return (0);
}
