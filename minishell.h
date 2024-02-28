/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:17:46 by fshields          #+#    #+#             */
/*   Updated: 2024/02/28 11:07:09 by fshields         ###   ########.fr       */
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

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct	s_data
{
	t_env	*env;
}			t_data;

//init.c
t_data	*init_data(char *env[]);

//input.c

//utils.c
char	*expand_env(char *str);
void	free_env_list(t_env *env_list);

//signals.c
void	init_signals(void);

//echo.c
int		ft_echo(int fd, char *str);
int		ft_old_echo(int fd, char *str, int flag);

//pwd.c
char	*get_pwd(void);
int		ft_print_pwd(int fd);

//env.c
int		ft_env(int fd, t_env *env);

//cd.c
int		ft_cd(char *path, t_env *env);

//exit.c
void	ft_exit(int status);

#endif