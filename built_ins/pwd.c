/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:50:36 by fshields          #+#    #+#             */
/*   Updated: 2024/02/28 08:52:27 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_pwd(void)
{
	char	*ret_path;

	ret_path = (char *) malloc(sizeof(char) * 100);
	if (getcwd(ret_path, 100) == NULL)
		return (NULL);
	return (ret_path);
}

int	ft_print_pwd(int fd)
{
	char	*pwd;
	
	pwd = get_pwd();
	if (write(fd, pwd, ft_strlen(pwd)) != (ssize_t) ft_strlen(pwd))
		return (1);
	if (write(fd, "\n", 1) != 1)
		return (1);
	free(pwd);
	return (0);
}
