/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_unsanitized_input.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:03:12 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/04 16:40:10 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static void	get_input_redir_mode(char **input, int i, t_sanit_comm *cmd)
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
}*/

/*static int	get_input_arg(char **arr, int i, t_sanit_comm *cmds)
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
	
}*/

/*static int	check_if_redirected(char **input, t_sanit_comm *cmd)
{
	//format is <word, where word will be the input file
	//there can be several in one command, and all should be saved, since the entirety of them will be the input
	//
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
}*/

static int	add_to_input_list(char **arr, int i, int j)
{
	//Step 1: duplicate the redir symbol and the rest of the string
	//step 2: if the 1st of 2nd redir symbol is how the str ends, strjoin the next str to it
}

static int	init_input_redir_list(char **arr, t_sanit_comm *cmds)
{
	int		i;
	int		j;
	char	quote;
	int		result;

	i = 0;
	j = 0;
	result = 0;
	while (arr[i] != NULL)
	{
		while (arr[i][j] != '\0')
		{
			if (arr[i][j] == '<' && check_if_quote_enclosed(arr[i], j) == 0)
			{
				result = add_to_input_list(arr, i, j);
				if (result == -1)
					return (-1);
			}
			j++;
		}
		i++;
	}
	return (result);
}

int	get_input_unsanit(char *str, t_data *commands)
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
	result = get_input_array(split_input, commands->unsanit_comms);
	return (result);
}
