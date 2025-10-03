/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:50:14 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/29 11:13:25 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_handler_exit(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	exit(130);
}

void	signal_handler_wait(int sig)
{
	(void)sig;
	g_sig_received = 2;
}

void	signal_handler_main(int sig)
{
	(void)sig;
	g_sig_received = 1;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signals(void (*signal_handler)(int))
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * 3 types of signal used in minishell:
 * (1) Ctrl C (SIGINT): $? = 130
 * -1- main: interrupt input, clean buffer and return a new promt in the
 * new line
 * -2- heredoc: exit
 * -3- execution: interrupt child process and exit
 * (2) Ctrl D : $? = 0
 * -1- main: exit minishell, print "exit"
 * -2- heredoc: exit heredoc, print "warning"
 * (3) SIGQUIT : ignored
 *
 *
 * 3 types of signal handler:
 * (1) exit: used for child process (both execution and heredoc) when
 * exit is required
 * (2) wait: after fork before witpid, used for parent process, to avoid
 * printing out $minishell more than 1 time
 * (3) main: used when there is only 1 process, continue printing $minishell
 * when a SIGINT happens
 */