/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 10:46:10 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/30 17:45:29 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "parsing.h"
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
/* =========================== Non-Builtin ===================================*/
void	execute(t_node *node, t_shell *shell);
int		exec_pipe(t_node *pipe_node, t_shell *shell);
int		exec_builtin(t_shell *shell, char **cmd);
int		exec_non_builtin(t_node *cmd, t_shell *shell);
int		open_files(t_node *node, int *in_fd, int *out_fd);
int		find_cmd_path(char **cmd, char **path, t_shell *shell);
void	clean_array(char **arr);
void	close_fd(int in_fd, int out_fd);
void	close_heredoc_fd(t_node *node);
int		check_access(char *path);
void	check_dir_cmd(char *path, int *flag);
int		check_dir_path(char *path, int *flag);
int		print_error_cmd(int flag, char *cmd_name);
int		print_error_path(int flag, char *cmd_name);
/* =========================== Builtin =======================================*/
int		builtin_pwd(char **cmd);
int		builtin_export(t_shell *shell, char **cmd);
void	print_envp(t_env *envp);
int		is_valid_identifier(char *name);
void	parse_export_arg(char *arg, char **name, char **value, int *equal_sign);
t_env	*is_env_exist(t_env *list, char *name);
int		builtin_cd(t_shell *shell, char **cmd);
int		count_arguments(char **cmd);
int		builtin_exit(t_shell *shell, char **cmd);
int		builtin_env(t_shell *shell, char **cmd);
int		builtin_unset(t_shell *shell, char **cmd);
int		builtin_echo(t_shell *shell, char **cmd);
int		exec_child_builtin(t_node *cmd, t_shell *shell);
int		exec_normal_builtin(t_node *cmd, t_shell *shell);
int		setup_redirections(t_node *nodes);
void	print_env_vars(t_env *env_list);

#endif