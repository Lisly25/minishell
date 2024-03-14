/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:37:43 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/14 15:00:20 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*check_if_existing_env(char *redirect, t_data *data)
{
	t_env	*env;
	int		i;

	env = data->env;
	i = 0;
	while (env != NULL)
	{
		while (env->name[i] != '\0' && redirect[i] != '\0' && \
		env->name[i] == redirect[i])
			i++;
		if (env->name[i] == '\0' && redirect[i] == '\0')
			return (env->name);
		i = 0;
		env = env->next;
	}
	return (NULL);
}

static int	detect_redirect(char *redirect)
{
	size_t	i;

	i = 0;
	while (redirect[i] != '\0')
	{
		if (redirect[i] == '\'')
		{
			i++;
			while (redirect[i] != '\'')
				i++;
		}
		if (redirect[i] != '$')
			i++;
		else
			break ;
	}
	if (i == ft_strlen(redirect))
		return (0);
	return (1);
}

int	detect_ambiguous_redirect(char	*redirect, t_data *data)
{
	char	*env_var_value;
	int		i;

	i = 0;
	if (detect_redirect(redirect) == 0)
		return (0);
	env_var_value = check_if_existing_env(redirect, data);
	if (env_var_value == NULL)
	{
		if (redirect[0] != '$')
			return (0);
		ft_printf("minishell 🐢: %s: ambiguous redirect\n", redirect);
		return (1);
	}
	while (env_var_value[i] != '\0')
	{
		if (env_var_value[i] == ' ')
		{
			ft_printf("minishell 🐢: %s: ambiguous redirect\n", redirect);
			return (1);
		}
		i++;
	}
	return (0);
}
