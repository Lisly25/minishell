/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:37:43 by skorbai           #+#    #+#             */
/*   Updated: 2024/03/15 15:47:20 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*check_if_existing_env(char *redirect, t_data *data)
{
	t_env	*env;
	int		i;
	int		j;

	env = data->env;
	i = 0;
	j = 1;
	while (env != NULL)
	{
		while (env->name[i] != '\0' && redirect[j] != '\0' && \
		env->name[i] == redirect[j])
		{
			i++;
			j++;
		}
		if (env->name[i] == '\0' && redirect[j] == '\0')
			return (env->value);
		i = 0;
		j = 1;
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

static int	check_for_space_in_expanded_value(char *str, t_data *data)
{
	char	*ptr_to_env_name;
	char	*env_value;
	int		i;

	i = 0;
	ptr_to_env_name = ft_strchr(str, '$');//not checking for null here, already checked that it contains '$'
	env_value = check_if_existing_env(ptr_to_env_name, data);
	if (env_value == NULL)
		return (0);
	while (env_value[i] != '\0')
	{
		if (env_value[i] == ' ')
		{
			ft_error_message("ambiguous redirect", str);
			return (1);
		}
		i++;
	}
	return (0);
}
//if there's several env variables:
//havng any env variable wih a space in it should give an error - but ours does not right now, if there's extra letters before it

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
			return (check_for_space_in_expanded_value(redirect, data));
		ft_error_message("ambiguous redirect", redirect);
		return (1);
	}
	while (env_var_value[i] != '\0')
	{
		if (env_var_value[i] == ' ')
		{
			ft_error_message("ambiguous redirect", redirect);
			return (1);
		}
		i++;
	}
	return (0);
}
