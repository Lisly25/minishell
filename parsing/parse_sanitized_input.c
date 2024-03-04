/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sanitized_input.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:03:12 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/01 17:06:31 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_input_source(char **input, int i, t_sanit_comm *cmd)
{
	size_t	j;

	j = 0;
	while (input[i][j] != '<')
		j++;
	if (input[i][j] != '\0')
		j++;
	if (input[i][j] == '<')
	{
		cmd->file_input = 'N';
		cmd->heredoc_input = 'Y';
	}
	else
	{
		cmd->file_input = 'Y';
		cmd->heredoc_input = 'N';
	}
	//we'll next need to check the next array to ther "right" of 'i':
	// - if 'i' was last, then: syntax error near unexpected token `newline'
	// - if not, then it'll either be de delimiter or the infile
}

static void	get_input_mode_sanit(char **input, t_sanit_comm *cmd)
{
	//format is <word, where word will be the input file
	//there can be several in one command, and always the last one will take precedent
	int	i;

	i = ft_get_arr_size;
	while (i >= 0)
	{
		if (ft_strrchr(input[i], '<') != NULL)
		{
			if (check_if_quote_enclosed(input[i], i) == 0)
			{
				get_input_source(input, i, cmd);
				return ;
			}
		}
		i--;
	}
	cmd->file_input = 'N';
	cmd->heredoc_input = 'N';
}

int	get_input_sanit(char *str, t_sanit_comm *commands)
{
	int		result;
	char	**split_input;

	split_input = ft_quoted_split(str);
	if (split_input == NULL)
		return (-1);
	if (check_for_max_consequitve_chars(split_input, '<') > 2)
	{
		ft_free_2d_array(split_input);
		ft_parse_error("syntax error near unexpected token `<<'");
	}
	get_input_mode_sanit(split_input, commands);
	if (commands->file_input == 'Y')
		result = get_infile_sanit(str, commands);
	else if (commands->heredoc_input == 'Y')
		result = get_hdoc_limiter_sanit(str, commands);
	else
		return (result);
}
