/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:37:43 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/21 12:37:59 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*check_if_existing_env(char *redirect, t_data *data)
{
	t_env	*env;
	int		i;
	char	*redir_start;

	redir_start = redirect;
	env = data->env;
	i = 0;
	while (env != NULL)
	{
		while (env->name[i] != '\0' && *redirect != '\0' && *redirect != '$' && \
		env->name[i] == *redirect)
		{
			i++;
			redirect++;
		}
		if (env->name[i] == '\0' && (*redirect == '\0' || *redirect == '$'))
			return (env->value);
		i = 0;
		redirect = redir_start;
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

int	detect_ambiguous_redirect(char	*redir, t_data *data)
{
	char	*env_var_value;
	char	*str;

	str = redir;
	if (detect_redirect(redir) == 0)
		return (0);
	while (*str != '\0')
	{
		if (*str == '$')
		{
			str++;
			env_var_value = check_if_existing_env(str, data);
			if (env_var_value == NULL)
			{
				if (str == (redir + 1) && (ft_strrchr(redir, '$') == (str - 1)))
					return (ft_ambi_redirect_error_msg(redir));
			}
			else if (ft_strchr(env_var_value, ' ') != NULL)
				return (ft_ambi_redirect_error_msg(redir));
		}
		str++;
	}
	return (0);
}
