/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:52:30 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/29 14:25:25 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_qsplit_frag_len(char *str, int i)
{
	int		len;
	char	quote;

	len = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			return (len);
		else if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			//ft_printf("%c found at %d\n", quote, i);
			i++;
			len++;
			while (str[i] != quote)
			{
				i++;
				len++;
			}
		}
		i++;
		len++;
	}
	return (len);
}

char	**qsplit_free_and_null(char **result)
{
	int	i;

	i = 0;
	while (result[i] != NULL)
		free(result[i++]);
	free(result);
	return (NULL);
}

int	update_main_split_post_cpy(char *s, int i)
{
	char	quote;

	while (s[i] != '\0')
	{
		if (s[i] == ' ')
		{
			//ft_printf("Main split should now be at %d\n", i);
			return (i);
		}
		if (s[i] == '\'' || s[i] == '\"')
		{
			quote = s[i];
			i++;
			while (s[i] != quote)
				i++;
		}
		i++;
	}
	//ft_printf("Main split should now be at %d\n", i);
	return (i);
}
