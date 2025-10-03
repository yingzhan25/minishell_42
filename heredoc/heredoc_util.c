/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 18:50:06 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/28 18:50:52 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*Write content to a pipe (fd)*/
int	expand_write(char *input, t_shell *shell, int pipe_w)
{
	char	*exp_input;

	exp_input = exp_heredoc(input, shell);
	free(input);
	if (write(pipe_w, exp_input, ft_strlen(exp_input)) == -1 || \
		write(pipe_w, "\n", 1) == -1)
		return (free(exp_input), close(pipe_w), perror("Write"), GENERAL_ERROR);
	free(exp_input);
	return (0);
}

/*Ctrl D*/
void	print_warning(char *s)
{
	ft_putstr_fd("warning: here-document delimited by end-of-file (wanted `", \
				STDOUT_FILENO);
	ft_putstr_fd(s, STDOUT_FILENO);
	ft_putstr_fd("')\n", STDOUT_FILENO);
}
