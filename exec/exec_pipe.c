/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:47:51 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/28 18:16:24 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*Global set to 2 during waiting if SIGINT;
write a newline when broken pipe and SIGINT happen together;
e.g. cat | ls*/
void	wait_process(int *pid, t_shell *shell)
{
	int	status1;
	int	status2;

	waitpid(pid[1], &status2, 0);
	waitpid(pid[0], &status1, 0);
	if (WIFEXITED(status2))
	{
		if (WEXITSTATUS(status2) == 0 && WTERMSIG(status1) == 13 \
		&& g_sig_received == 2)
		{
			write(STDOUT_FILENO, "\n", 1);
			g_sig_received = 0;
		}
		shell->exit_code = WEXITSTATUS(status2);
	}
	else if (WIFSIGNALED(status2))
		shell->exit_code = 128 + WTERMSIG(status2);
}

/*If 1st child failed, 2nd child has to wait before exit, to avoid zombie*/
int	failed_fork(int	*pid, int *pfd, int i, t_shell *shell)
{
	close(pfd[0]);
	close(pfd[1]);
	perror("Fork");
	shell->exit_code = GENERAL_ERROR;
	if (i == 1)
		waitpid(pid[0], NULL, 0);
	return (shell->exit_code);
}

void	exec_pipe_child(int *pfd, t_node *pipe_node, t_shell *shell, int left)
{
	if (left)
	{
		close(pfd[0]);
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[1]);
		execute(pipe_node->pipe.left, shell);
		exit(shell->exit_code);
	}
	else
	{
		close(pfd[1]);
		dup2(pfd[0], STDIN_FILENO);
		close(pfd[0]);
		execute(pipe_node->pipe.right, shell);
		exit(shell->exit_code);
	}
}

/*Execute left node first, and then right node;
return when the right node is not pipe anymore;
always take the rightest command for exit code*/
int	exec_pipe(t_node *pipe_node, t_shell *shell)
{
	int	pfd[2];
	int	pid[2];

	if (pipe(pfd) == -1)
	{
		shell->exit_code = GENERAL_ERROR;
		return (perror("Pipe"), shell->exit_code);
	}
	pid[0] = fork();
	if (pid[0] == -1)
		return (failed_fork(pid, pfd, 0, shell));
	else if (!pid[0])
		exec_pipe_child(pfd, pipe_node, shell, 1);
	pid[1] = fork();
	if (pid[1] == -1)
		return (failed_fork(pid, pfd, 1, shell));
	else if (!pid[1])
		exec_pipe_child(pfd, pipe_node, shell, 0);
	close(pfd[0]);
	close(pfd[1]);
	setup_signals(signal_handler_wait);
	wait_process(pid, shell);
	setup_signals(signal_handler_main);
	return (shell->exit_code);
}
