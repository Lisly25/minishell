/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:59:29 by fshields          #+#    #+#             */
/*   Updated: 2024/02/22 16:56:03 by fshields         ###   ########.fr       */
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

static char	*get_cd_path(char *input)
{
	char 	*pwd;
	char	*path;

	pwd = get_pwd();
	if (ft_strncmp(input, "..", 2) == 0)
	{
		if (ft_strlen(input) == 2)
			path = trim_end_of_path(pwd);
		else
			path = append_path(trim_end_of_path(pwd), (input + 3));
	}
	else if (ft_strncmp(input, "/Users", 6) == 0)
		path = input;
	else
		path = append_path(pwd, input);
	if (!(ft_strncmp(input, "..", 2) == 0 && ft_strlen(input) == 2))
		free(pwd);
	return (path);
}

int ft_cd(char *input)
{
	char	*path;

	path = get_cd_path(input);
	if (chdir(path) != 0)
	{
		free(path);
		return (1);
	}
	if (ft_strncmp(input, path, ft_strlen(input)) != 0)
		free(path);
	return (0);
}