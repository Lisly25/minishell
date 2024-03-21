/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:59:29 by fshields          #+#    #+#             */
/*   Updated: 2024/03/21 16:13:24 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	exists(char *path)
{
	int	acc;

	acc = access(path, F_OK);
	if (acc < 0)
		return (0);
	return (1);
}

static int	is_dir(char *path)
{
	int	fd;

	fd = open(path, O_DIRECTORY);
	if (fd < 0)
		return (0);
	close (fd);
	return (1);
}

static void	handle_bad_path(char **oldpwd, char *input, t_env **env)
{
	if (*oldpwd)
		update_dir('o', *oldpwd, env);
	ft_putstr_fd("minishell 🐢: cd: ", 2);
	ft_putstr_fd(input, 2);
	if (!exists(input))
		ft_putstr_fd(": No such file or directory\n", 2);
	else if (exists(input) && !is_dir(input))
		ft_putstr_fd(": Not a directory\n", 2);
}

static void	free_both(char **pwd, char **path)
{
	free(*pwd);
	free(*path);
}

int	ft_cd(char *input, t_env **env)
{
	char	*pwd;
	char	*oldpwd;
	char	*path;

	if (!input)
		path = ft_strdup(getenv("HOME"));
	else
		path = ft_strdup(input);
	pwd = get_pwd();
	oldpwd = getenv("OLDPWD");
	if (already_in_list("OLDPWD", *env))
		update_dir('o', pwd, env);
	if (!exists(path) || chdir(path) != 0)
	{
		handle_bad_path(&oldpwd, path, env);
		free_both(&pwd, &path);
		return (1);
	}
	free(pwd);
	pwd = get_pwd();
	if (already_in_list("PWD", *env))
		update_dir('p', pwd, env);
	free_both(&pwd, &path);
	return (0);
}
