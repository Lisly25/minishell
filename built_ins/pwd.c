/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:50:36 by fshields          #+#    #+#             */
/*   Updated: 2024/03/15 15:33:54 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_pwd(void)
{
	char	*ret_path;

	ret_path = (char *) malloc(sizeof(char) * 300);
	if (getcwd(ret_path, 300) == NULL)
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
