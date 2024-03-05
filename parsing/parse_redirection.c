/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:30:24 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/05 18:01:19 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	extract_redir(char *str, int i, t_vector *redir_array, char c)
{
	char	*buffer;

	buffer = ft_strdup_only_char_c_str(c, str, i);
	if (buffer == NULL)
		return (MALLOC_ERROR);
	if (vector_add_back(redir_array, buffer) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	while (str[i] == c)
		str[i++] = ' ';
	while (str[i] != '\0' && str[i] == ' ')
		i++;
	buffer = ft_strdup_from_i_to_char(c, str, i, ' ');
	if (buffer == NULL)
		return (MALLOC_ERROR);
	while (str[i] != '\0' && str[i] != c && str[i] != ' ')
		str[i++] = ' ';
	return (0);
}

int	extract_redir_array(char *str, char c, t_unsanit_comm *cmd)
{
	int			i;
	int			result;
	t_vector	*redir_array;

	i = 0;
	result = 0;
	redir_array = vector_new(1);
	if (redir_array == NULL)
		return (MALLOC_ERROR);
	while (str[i] != '\0')
	{
		if (str[i] == c && check_if_quote_enclosed(str, i) == 0)
		{
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
