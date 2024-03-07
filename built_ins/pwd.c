/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:50:36 by fshields          #+#    #+#             */
/*   Updated: 2024/03/05 16:20:15 by fshields         ###   ########.fr       */
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

int	ft_print_pwd(void)
{
	char	*pwd;
	
	pwd = get_pwd();
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
