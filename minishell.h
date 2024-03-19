/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:17:46 by fshields          #+#    #+#             */
/*   Updated: 2024/03/19 11:25:56 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

void rl_replace_line (const char *, int);
void rl_clear_history (void);

# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "parse.h"

//init.c
int		get_list_size(t_env *list);
t_env	*new_node(char *name, char *value);
void	add_to_back(t_env **list, t_env *new);
t_data	*init_data(char *env[]);

//input.c
void	free_comm(t_data *data);

//built_utils.c
char	*expand_env(char *str);
void	free_env_list(t_env **env_list);
int		already_in_list(char *arg, t_env *env);
void	update_dir(char dir, char *value, t_env **env);

//signals.c
void	reset_signals(void);
void	default_signals(void);

//echo.c
int		ft_echo(char *str);

//pwd.c
char	*get_pwd(void);
int		ft_print_pwd(void);

//env.c
int		ft_env(t_env *env);

//cd.c
int		ft_cd(char *path, t_env **env);

//exit.c
void	ft_exit(char *status, t_data *data);
//export.c
int		ft_export(char *arg, t_env **env);
void	reset_printed(t_env **env);
int		all_printed(t_env **env);

//export_utils.c
void	display_vars(t_env **env);
void	ammend_var(char *arg, t_env **env);
int		add_var(char *arg, t_env **env);

//unset.c
int		ft_unset(char *arg, t_env **env);

//execution.c
int		child_process(t_data *data, t_comm *comm);
int		execute(t_data *data);

//execution_utils.c
char	*find_path(t_comm *command, char **env_s, t_data *data);
int		detect_built_in(char *command);
int		run_built_in(char *arg, int code, t_data *data);
void	wait_for_children(t_data *data);

//execution_utils_2.c
void	save_io(int io[]);
void	reset_io(int io[]);
char	**env_to_str(t_env	*env);

//execution_external.c
int		init_children_and_fds(t_data *data);
int		open_redirects(t_data *data, int i);
int		redirect(t_comm *cmd);

//open_redirections.c
int		open_read(char **redirect, int j, int i, t_data *data);
int		open_write(char **redirect, int j, t_data *data);
void	close_file(t_data *data, int fd, int j, char **file_arr);

//redirect_utils.c
int		check_if_last_redirect(char c, char **redirect, int j);

//redirect_errors.c
int		detect_ambiguous_redirect(char	*redirect, t_data *data);

//execution_path.c
char	*find_path_from_path_env(char *cmd, char **env_s, t_data *data);
char	*find_absolute_path(char *cmd, t_data *data);
char	*find_relative_path(char *cmd, t_data *data);

//execution_path_utils.c
char	**get_path_env_array(char **env_s, char *cmd, t_data *data);
int		check_access_to_command(char *path, char *cmd, t_data *data);

//heredoc.c
int		get_heredoc(t_data *data);
int		delete_heredocs(t_data *data);

//heredoc_utils.c
char	*derive_heredoc_name(int num);

//errors.c
void	ft_message_and_exit(t_data *data, int code);
void	ft_free_2d_array(char **arr);
void	ft_free_t_data_struct(t_data *data);
void	ft_msg_free_and_exit(t_data *data, int code, char *msg, char *target);
void	*ft_error_message_and_return_null(char *msg, char *target);

//errors_2.c
void	ft_error_message(char *message, char *target);
void	free_comm(t_data *data);

//handle_exit_codes.c
void	handle_exit_codes(t_data *data);

#endif