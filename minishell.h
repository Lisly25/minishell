/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:17:46 by fshields          #+#    #+#             */
/*   Updated: 2024/02/22 16:52:41 by fshields         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

void rl_replace_line (const char *, int);
void rl_clear_history (void);

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include "libft/libft.h"

//read_line.c
void	handle_signal(int sig);

//echo.c
int		ft_echo(int fd, char *str, int flag);

//pwd.c
char	*get_pwd(void);
int		ft_print_pwd(int fd);

//env.c
int		ft_env(int fd, char *env[]);

//cd.c
int		ft_cd(char *path);

#endif