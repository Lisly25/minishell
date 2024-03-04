/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sanitized_input.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:03:12 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/04 10:54:57 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_input_redir_mode(char **input, int i, t_sanit_comm *cmd)
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

static int	get_input_arg(char **arr, int i, t_sanit_comm *cmds)
{
	int	arr_len;
	int	j;
	int	str_len;

	arr_len = ft_get_arr_size(arr);
	j = 0;
	str_len = (int)ft_strlen(arr[i]);
	while (arr[i][j] != '<')
		j++;
	if (j == str_len)
	{
		i++;
		if (arr[i] == NULL)
			return (ft_parse_error("syntax error near unexpected token `newline'"));
		
	}
	
}

static int	check_if_redirected(char **input, t_sanit_comm *cmd)
{
	//format is <word, where word will be the input file
	//there can be several in one command, and always the last one will take precedent
	int		i;
	int		result;
	int		input_redir_loc;
	int		redir_char;

	i = ft_get_arr_size;
	while (i >= 0)
	{
		ptr_to_redir = ft_strrchr_index(input[i], '<');
		if (ptr_to_redir != NULL)
		{
			if (check_if_quote_enclosed(input[i], i) == 0)//this ain't good, second arg should be j
			{
				get_input_redir_mode(input, i, cmd);
				result = get_input_arg(input, i, cmd);
				return (result);
			}
		}
		i--;
	}
	cmd->file_input = 'N';
	cmd->heredoc_input = 'N';
	return (0);
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
		return (ft_parse_error("syntax error near unexpected token `<<'"));
	}
	result = check_if_redirected(split_input, commands);
	return (result);
}
