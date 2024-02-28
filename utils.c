/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 08:35:42 by fshields          #+#    #+#             */
/*   Updated: 2024/02/28 07:42:10 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_env(char *str)
{
	size_t	len;
	char	*ret;
	char	*var;
	
	len = 0;
	while (ft_isprint(str[len]) > 0 && str[len] != ' ')
		len ++;
	len --;
	var = ft_substr(str, 1, len);
	if (!var)
		return (NULL);
	ret = getenv(var);
	free(var);
	return (ret);
}

void	free_env_list(t_env *env_list)
{
	t_env	*temp;
	
	while (env_list)
	{
		temp = env_list->next;
		free(env_list->name);
		free(env_list->value);
		free(env_list);
		env_list = temp;
	}
}
