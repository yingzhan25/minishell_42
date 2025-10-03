/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 20:13:50 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/29 10:48:48 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * is_builtin checks whether the given command is a shell builtin.
 *
 * @param arg : The command string to check.
 *
 * Returns:
 * - 0 if the command is a recognized builtin (echo, cd, exit, 
 * pwd, export, unset, env).
 * - 1 if the command is not a builtin or if arg is NULL.
 *
 * Example:
 * - is_builtin("cd") returns 0
 * - is_builtin("ls") returns 1
 *
 * This function helps decide whether to execute the command
 * internally (builtin) or as an external program.
 */
static int	is_builtin(char *arg)
{
	if (!arg)
		return (1);
	if (!ft_strcmp(arg, "echo")
		|| !ft_strcmp(arg, "cd")
		|| !ft_strcmp(arg, "exit")
		|| !ft_strcmp(arg, "pwd")
		|| !ft_strcmp(arg, "export")
		|| !ft_strcmp(arg, "unset")
		|| !ft_strcmp(arg, "env"))
		return (0);
	return (1);
}

/*
 * is_child_builtin checks whether a given command should be executed
 * in a child process for builtins that normally produce output or
 * affect only the current process environment minimally.
 *
 * @param arg : The command string to check.
 *
 * Returns:
 * - 0 if the command is a child-executable builtin (env, pwd, echo).
 * - 1 if the command should not be executed in a child process.
 *
 * Example:
 * - is_child_builtin("echo") returns 0
 * - is_child_builtin("cd") returns 1
 *
 * This distinction allows the shell to decide whether a builtin
 * needs its own process (child) or can run in the main shell process.
 */
static int	is_child_builtin(char *arg)
{
	if (!ft_strcmp(arg, "env") || !ft_strcmp(arg, "pwd")
		|| !ft_strcmp(arg, "echo"))
		return (0);
	return (1);
}

/*
 * exec_simple_command executes a single command node, determining
 * whether it is a builtin or external command, and whether the builtin
 * should run in a child process or the main shell process.
 *
 * @param cmd   : The command node containing the command and arguments.
 * @param shell : The shell structure holding environment and state.
 *
 * Returns:
 * - Exit code of the executed command.
 *
 * Logic:
 * 1. If the command exists and is a builtin:
 *      - If it can run in a child (env, pwd, echo), use exec_child_builtin.
 *      - Otherwise, run in the current shell process with exec_normal_builtin.
 * 2. If the command is not a builtin, run it as an external command
 *    with exec_non_builtin.
 *
 * Example:
 * - exec_simple_command(cmd_for_pwd, shell) executes "pwd" in a child.
 * - exec_simple_command(cmd_for_cd, shell) executes "cd" in the shell process.
 */
int	exec_simple_command(t_node *cmd, t_shell *shell)
{
	if (cmd->cmd.cmd && !is_builtin(cmd->cmd.cmd[0]))
	{
		if (!is_child_builtin(cmd->cmd.cmd[0]))
			return (exec_child_builtin(cmd, shell));
		else
			return (exec_normal_builtin(cmd, shell));
	}
	else
		return (exec_non_builtin(cmd, shell));
}

/*
 * execute decides how to run a given command node based on its type.
 *
 * @param node  : The command node to execute.
 * @param shell : The shell structure containing environment and state.
 *
 * Logic:
 * 1. If the node represents a pipe, call exec_pipe to handle the pipeline.
 * 2. Otherwise, execute the node as a simple command with exec_simple_command.
 *
 * The exit code of the executed command or pipeline is stored 
 * in shell->exit_code.
 *
 * Example:
 * - For a single command like "ls", exec_simple_command is called.
 * - For a command like "ls | grep txt", exec_pipe handles the pipeline.
 */
void	execute(t_node *node, t_shell *shell)
{
	if (node->type == PIPE)
		shell->exit_code = exec_pipe(node, shell);
	else
		shell->exit_code = exec_simple_command(node, shell);
}
