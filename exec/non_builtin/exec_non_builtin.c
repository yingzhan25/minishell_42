/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_non_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:13:58 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/29 11:45:58 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	redir_child(int in_fd, int out_fd)
{
	if (in_fd != -1)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != -1)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
}

/*If execve succeeds, exit and clean up automatically;
if error occurs, clean up and exit manually*/
static int	exec_child(t_node *cmd, int in_fd, int out_fd, t_shell *shell)
{
	char	*path;
	char	**env;

	setup_signals(signal_handler_exit);
	signal(SIGQUIT, SIG_DFL);
	path = NULL;
	redir_child(in_fd, out_fd);
	shell->exit_code = find_cmd_path(cmd->cmd.cmd, &path, shell);
	if (shell->exit_code)
		exit(shell->exit_code);
	env = envp_to_array(shell->env_list);
	if (!env)
	{
		ft_putstr_fd("Environment not found", STDERR_FILENO);
		free(path);
		exit(GENERAL_ERROR);
	}
	if (execve(path, cmd->cmd.cmd, env) == -1)
	{
		perror("Execve");
		free(path);
		clean_array(env);
		exit(GENERAL_ERROR);
	}
	return (0);
}

/*Print error msg to stdout when SIGQUIT*/
static int	exec_check_status(int status, t_shell *shell)
{
	if (WIFEXITED(status))
	{
		shell->exit_code = WEXITSTATUS(status);
		return (setup_signals(signal_handler_main), shell->exit_code);
	}
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status))
		{
			if (WTERMSIG(status) == 3)
				ft_putstr_fd("Quit (core dumped)", STDOUT_FILENO);
			write(STDOUT_FILENO, "\n", 1);
		}
		shell->exit_code = 128 + WTERMSIG(status);
		return (setup_signals(signal_handler_main), shell->exit_code);
	}
	return (0);
}

/*Print a newline when child process got SIGINT or SIGQUIT, e.g. cat*/
static int	exec_cmd(t_node *cmd, t_shell *shell, int in_fd, int out_fd)
{
	int	pid;
	int	status;

	pid = -1;
	pid = fork();
	if (pid == -1)
		return (perror("fork"), close_fd(in_fd, out_fd), GENERAL_ERROR);
	else if (!pid)
		exec_child(cmd, in_fd, out_fd, shell);
	setup_signals(signal_handler_wait);
	close_fd(in_fd, out_fd);
	waitpid(pid, &status, 0);
	return (exec_check_status(status, shell));
}

/*Check redirection first, if no cmd, exit with 0,
e.g. "", '', <<1, $EMPTY*/
int	exec_non_builtin(t_node *cmd, t_shell *shell)
{
	int	in_fd;
	int	out_fd;

	in_fd = -1;
	out_fd = -1;
	if (cmd->cmd.redir_token)
	{
		shell->exit_code = open_files(cmd, &in_fd, &out_fd);
		if (shell->exit_code)
			return (close_heredoc_fd(cmd), close_fd(in_fd, out_fd), \
			shell->exit_code);
	}
	if (!cmd->cmd.cmd)
	{
		shell->exit_code = 0;
		return (close_fd(in_fd, out_fd), shell->exit_code);
	}
	return (exec_cmd(cmd, shell, in_fd, out_fd));
}
