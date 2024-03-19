/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:59:29 by fshields          #+#    #+#             */
/*   Updated: 2024/03/19 15:54:39 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*trim_end_of_path(char *path)
{
	char *ptr;

	ptr = path;
	while (*(ptr + 1))
		ptr ++;
	while (*ptr != '/')
		*(ptr--) = '\0';
	*(ptr) = '\0';
	return (path);
}

static char *append_path(char *pwd, char *append)
{
	char	*final_path;
	char	*rtn;

	final_path = (char *)malloc(sizeof(char) * (ft_strlen(pwd) + ft_strlen(append) + 2));
	if (!final_path)
		return (NULL);
	rtn = final_path;
	while (*pwd)
		*(final_path++) = *(pwd++);
	*(final_path++) = '/';
	while (*append)
		*(final_path++) = *(append++);
	*final_path = '\0';
	return (rtn);
}

static int	contains_dots(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (ft_strnstr(path, "/.", len) != NULL)
		return (1);
	else if (ft_strnstr(path, "/..", len) != NULL)
		return (1);
	else if (ft_strnstr(path, "./", len) != NULL)
		return (1);
	else if (ft_strnstr(path, "../", len) != NULL)
		return (1);
	return (0);
}

static void	expand_dots(char **path)
{
	char	*cpy_to;
	char	*cpy_from;

	cpy_from = ft_strnstr(*path, "/.", ft_strlen(*path)) + 2;
	cpy_to = cpy_from - 3;
	if (*cpy_from == '.')
	{
		cpy_from ++;
		while (*cpy_to != '/' && cpy_to != *path)
			cpy_to --;
	}
	else
		cpy_to ++;
	while (*cpy_from)
		*(cpy_to++) = *(cpy_from++);
	*cpy_to = '\0';
}

static void	handle_dots(char **path)
{
	char	*pwd;

	pwd = get_pwd();
	if (ft_strncmp(*path, "..", 2) == 0 && ft_strlen(*path) == 2)
		free(*path);
	if (ft_strncmp(*path, ".", 1) == 0 && ft_strlen(*path) == 1)
		free(*path);
	if (ft_strncmp(*path, "..", 2) == 0)
	{
		if (ft_strlen(*path) == 2)
			*path = trim_end_of_path(ft_strdup(pwd));
		else
			*path = append_path(trim_end_of_path(pwd), (*path) + 3);
	}
	else if (ft_strncmp(*path, ".", 1) == 0)
	{
		if (ft_strlen(*path) == 1)
			*path = ft_strdup(pwd);
		else
			*path = append_path(pwd, (*path) + 2);
	}
	else
		expand_dots(path);
	free(pwd);
}

// char	*get_complex_path(char *input)
// {
// 	char	*path;
// 	int		i;

// 	i = 0;
// 	path = ft_strdup(input);
// 	while (contains_dots(path))
// 		handle_dots(&path);
// 	return (path);
// }

static char	*get_cd_path2(char *input)
{
	char	*pwd;
	char	*path;

	pwd = get_pwd();
	path = ft_strdup(input);
	while (contains_dots(path))
		handle_dots(&path);
	if (ft_strncmp(input, "/Users", 6) == 0)
		path = input;
	else
		path = append_path(pwd, input);
	if (!(ft_strncmp(input, "..", 2) == 0 && ft_strlen(input) == 2))
		free(pwd);
	return (path);
}

// static char	*get_cd_path(char *input)
// {
// 	char 	*pwd;
// 	char	*path;

// 	pwd = get_pwd();
// 	if (ft_strncmp(input, "..", 2) == 0)
// 	{
// 		if (ft_strlen(input) == 2)
// 			path = trim_end_of_path(pwd);
// 		else
// 			path = append_path(trim_end_of_path(pwd), (input + 3));
// 	}
// 	else if (contains_dots(input))
// 		path = get_complex_path(input);
// 	else if (ft_strncmp(input, "/Users", 6) == 0)
// 		path = input;
// 	else
// 		path = append_path(pwd, input);
// 	if (!(ft_strncmp(input, "..", 2) == 0 && ft_strlen(input) == 2))
// 		free(pwd);
// 	return (path);
// }

static void	handle_bad_path(char **oldpwd, char *input, t_env **env)
{
	if (*oldpwd)
		update_dir('o', *oldpwd, env);
	ft_putstr_fd("minishell 🐢: cd: ", 2);
	ft_putstr_fd(input, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

int ft_cd(char *input, t_env **env)
{
	char	*path;
	char	*pwd;
	char	*oldpwd;

	path = get_cd_path2(input);
	pwd = get_pwd();
	oldpwd = getenv("OLDPWD");
	if (already_in_list("OLDPWD", *env))
		update_dir('o', pwd, env);
	if (chdir(path) != 0)
	{
		free(pwd);
		free(path);
		handle_bad_path(&oldpwd, input, env);
		return (1);
	}
	free(pwd);
	pwd = get_pwd();
	if (already_in_list("PWD", *env))
		update_dir('p', pwd, env);
	free(pwd);
	if (ft_strncmp(input, path, ft_strlen(input)) != 0)
		free(path);
	return (0);
}
