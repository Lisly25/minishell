/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fshields <fshields@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:17:46 by fshields          #+#    #+#             */
/*   Updated: 2024/02/29 15:40:39 by fshields         ###   ########.fr       */
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
# include <limits.h>
# include "libft/libft.h"
# include "parse.h"

typedef struct s_env
{
	int				printed;
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct	s_data
{
	t_env	*env;
}			t_data;

//init.c
int		get_list_size(t_env *list);
t_env	*new_node(char *name, char *value);
void	add_to_back(t_env **list, t_env *new);
t_data	*init_data(char *env[]);

//input.c

//built_utils.c
char	*expand_env(char *str);
void	free_env_list(t_env **env_list);
int		already_in_list(char *arg, t_env *env);

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
int		ft_cd(char *path, t_env **env);

//exit.c
void	ft_exit(int status);

//export.c
int		ft_export(int fd, char *arg, t_env **env);
void	reset_printed(t_env **env);
int		all_printed(t_env **env);

//export_utils.c
void	display_one_var(int fd, t_env *ptr);
void	display_vars(int fd, t_env **env);
void	ammend_var(char *arg, t_env **env);
int		add_var(char *arg, t_env **env);

//unset.c
int		ft_unset(char *arg, t_env **env);

#endif