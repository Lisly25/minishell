/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:50:36 by fshields          #+#    #+#             */
/*   Updated: 2024/03/21 14:41:42 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_pwd(void)
{
	char	*ret_path;

	ret_path = getcwd(NULL, 0);
	if (!ret_path)
		return (NULL);
	return (ret_path);
}

int	ft_print_pwd(void)
{
	char	*pwd;

	pwd = get_pwd();
	if (!pwd)
		return (MALLOC_ERROR);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
