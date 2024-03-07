/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split_pipes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 09:52:32 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/07 10:30:54 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_frags(char *str)
{
	int		count;
	int		i;
	char	quote;

	i = 0;
	count = 1;
	while (str[i] != '\0')
	{
		//by this point, we already tested for the first char being |, no need to repeat it here
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			while (str[i] != quote)
				i++;
		}
		if (str[i] == '|' && str[i + 1] != '\0')//we have already checked for double pipes and ending with pipes by this point
			count++;
		i++;
	}
	return (count);
}

static char	**init_p_split_result(char *str)
{
	char	**result;
	int		frag_count;

	frag_count = count_frags(str);
	result = (char **)malloc((sizeof(char *) * (frag_count + 1)));
	return (result);
}

char	**pipe_split(char *s)
{
	char	**result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = init_p_split_result(s);
	if (result == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] != '|')
		{
			result[j] = quote_split_strdup(s, i, '|');
			if (result[j] == NULL)
				return (qsplit_free_and_null(result));
			j++;
			i = update_main_split_post_cpy(s, i, '|');
		}
		if (s[i] == '|')
			i++;
	}
	result[j] = NULL;
	return (result);
}
