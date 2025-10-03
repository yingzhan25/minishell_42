/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:21:52 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/29 17:17:00 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

/**
 * g_sig_received is used to indicate a received signal made by user;
 * 0: no signal;
 * 1: recieved SIGINT from main or heredoc -- interactive mode;
 * 2: received SIGINT from wait -- child process executing;
 */
sig_atomic_t	g_sig_received = 0;

static int	read_input(t_shell *shell, char **input)
{
	*input = readline("minishell$ ");
	if (g_sig_received == 1)
	{
		shell->exit_code = 130;
		g_sig_received = 0;
	}
	if (!*input)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		return (1);
	}
	if (**input)
		add_history(*input);
	return (0);
}

static void	shell_loop(t_shell *shell)
{
	char	*input;

	while (1)
	{
		if (read_input(shell, &input))
			break ;
		shell->nodes = ft_parse(shell, input);
		if (!shell->nodes)
		{
			free(input);
			continue ;
		}
		find_heredoc(shell->nodes, shell);
		if (g_sig_received == 1)
		{
			free_ast(shell->nodes);
			free(input);
			g_sig_received = 0;
			continue ;
		}
		execute(shell->nodes, shell);
		free_ast(shell->nodes);
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = init_envp(envp);
	if (!shell)
		return (ft_putstr_fd("Failed to initialize shell", \
				STDERR_FILENO), GENERAL_ERROR);
	setup_signals(signal_handler_main);
	shell_loop(shell);
	clean_shell(shell);
	rl_clear_history();
	return (0);
}
