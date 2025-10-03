/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:56:08 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/29 10:36:04 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	* restore_fds function restores the original file descriptors for stdin, 
	* stdout, and stderr.
	*
	* @param in  : Original file descriptor for standard input (stdin).
	* @param out : Original file descriptor for standard output (stdout).
	* @param err : Original file descriptor for standard error (stderr).
	*
	* Behavior:
	* - Uses dup2 to restore the saved file descriptors to their respective 
	* standard streams.
	* - Closes the saved file descriptors after restoring them.
	*
	* This is typically used after temporarily redirecting 
	* input/output in a command execution.
 */
static void	restore_fds(int in, int out, int err)
{
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	dup2(err, STDERR_FILENO);
	close(in);
	close(out);
	close(err);
}

/*
 * exec_builtin function executes a shell builtin command.
 *
 * @param shell : Pointer to the shell structure containing 
 * 	environment and state.
 * @param cmd   : Array of strings representing the command and its arguments.
 *
 * Returns:
 * - The return value of the executed builtin command.
 *
 * Behavior:
 * - Compares the first string of cmd with builtin names ("echo", "pwd", etc.).
 * - Calls the corresponding builtin function if a match is found.
 * - Returns 0 if no builtin matches or the return value of the executed builtin
 *
 * Note:
 * - This function does not handle external commands; it only executes builtins.
 */
int	exec_builtin(t_shell *shell, char **cmd)
{
	int	bool;

	bool = 0;
	if (!ft_strcmp(cmd[0], "echo"))
		bool = builtin_echo(shell, cmd);
	if (!ft_strcmp(cmd[0], "pwd"))
		bool = builtin_pwd(cmd);
	if (!ft_strcmp(cmd[0], "export"))
		bool = builtin_export(shell, cmd);
	if (!ft_strcmp(cmd[0], "cd"))
		bool = builtin_cd(shell, cmd);
	if (!ft_strcmp(cmd[0], "exit"))
		bool = builtin_exit(shell, cmd);
	if (!ft_strcmp(cmd[0], "env"))
		bool = builtin_env(shell, cmd);
	if (!ft_strcmp(cmd[0], "unset"))
		bool = builtin_unset(shell, cmd);
	return (bool);
}

/*
 * exec_child_builtin function executes a builtin command in a child process.
 *
 * @param node  : Pointer to the AST node containing the command and 
 * 	redirections.
 * @param shell : Pointer to the shell structure containing 
 * 	environment and state.
 *
 * Returns:
 * - The exit status of the executed builtin command.
 *
 * Behavior:
 * - Forks a child process.
 * - In the child:
 *     - Sets up input/output redirections if any.
 *     - Executes the builtin command using exec_builtin().
 * - In the parent:
 *     - Waits for the child to finish.
 *     - Stores the child's exit code in shell->exit_code.
 *
 * Notes:
 * - Handles errors from fork and redirection setup.
 * - Ensures that builtin commands can work with redirections in pipelines.
 */
int	exec_child_builtin(t_node *node, t_shell *shell)
{
	int	status;
	int	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), GENERAL_ERROR);
	if (!pid)
	{
		if (setup_redirections(node))
			exit (1);
		exit(exec_builtin(shell, node->cmd.cmd));
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		shell->exit_code = WEXITSTATUS(status);
		return (WEXITSTATUS(status));
	}
	return (1);
}

/*
 * exec_normal_builtin function executes a builtin command 
 	in the current process.
 *
 * @param cmd   : Pointer to the AST node containing 
 * 	the command and redirections.
 * @param shell : Pointer to the shell structure 
 * 	containing environment and state.
 *
 * Returns:
 * - The exit status of the executed builtin command.
 *
 * Behavior:
 * - Saves the current standard input/output/error file descriptors.
 * - If the command has redirections, sets them up temporarily.
 * - Executes the builtin command using exec_builtin().
 * - Restores the original standard file descriptors 
 * to avoid affecting the shell.
 *
 * Notes:
 * - Useful for builtins that must run in the 
 * current process context (e.g., cd, export).
 * - Handles errors from redirection setup gracefully.
 */
int	exec_normal_builtin(t_node *cmd, t_shell *shell)
{
	int	saved_in;
	int	saved_out;
	int	saved_err;
	int	exit_code;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	saved_err = dup(STDERR_FILENO);
	exit_code = 1;
	if (cmd->cmd.redir_token && setup_redirections(cmd))
		return (restore_fds(saved_in, saved_out, saved_err), exit_code);
	restore_fds(saved_in, saved_out, saved_err);
	exit_code = exec_builtin(shell, cmd->cmd.cmd);
	return (exit_code);
}
