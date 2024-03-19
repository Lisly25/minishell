/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:30:24 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/18 15:40:44 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	extract_redir(char *str, int i, t_vector *redir_array, char c)
{
	char	*buffer;
	char	opposite_redir;
	int		k;

	if (c == '<')
		opposite_redir = '>';
	else
		opposite_redir = '<';
	buffer = ft_strdup_only_char_c_str(c, str, i);
	if (buffer == NULL)
		return (MALLOC_ERROR);
	if (vector_add_back(redir_array, buffer) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	while (str[i] == c)
		str[i++] = ' ';
	while (str[i] != '\0' && str[i] == ' ')
		i++;
	buffer = ft_strdup_from_i_to_char(c, str, i);
	if (buffer == NULL)
		return (MALLOC_ERROR);
	if (vector_add_back(redir_array, buffer) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	k = detect_redirect_limit(i, str, opposite_redir, c);
	while (i < k)
		str[i++] = ' ';
	return (0);
}

static int	extract_redir_array(char *str, t_vector *redir_array)
{
	int		i;
	int		result;
	char	c;	

	i = 0;
	result = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '<' || str[i] == '>') && check_if_quoted(str, i) == 0)
		{
			c = str[i];
			result = extract_redir(str, i, redir_array, c);
			if (result == MALLOC_ERROR)
			{
				free_vector(redir_array);
				return (MALLOC_ERROR);
			}
			i = 0;
		}
		else
			i++;
	}
	return (result);
}

int	add_redir_data_to_parse_struct(char *str, t_comm *cmd)
{
	t_vector	*redir_array;
	int			result;

	redir_array = vector_new(1);
	if (redir_array == NULL)
		return (MALLOC_ERROR);
	result = extract_redir_array(str, redir_array);
	if (result == MALLOC_ERROR)
		return (MALLOC_ERROR);
	if (redir_array->used_nodes != 0)
		cmd->redirect = redir_array->text;
	else
		cmd->redirect = NULL;
	free(redir_array);
	return (result);
}
