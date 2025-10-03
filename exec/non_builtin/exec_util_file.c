/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 10:33:16 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/28 19:36:26 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*If more than 1 redirection, close previous one immediately*/
static int	open_in_out_append(int *fd, t_redir_token *tmp)
{
	if (*fd != -1)
		close (*fd);
	if (tmp->redir_type == IN)
		*fd = open(tmp->file, O_RDONLY);
	else if (tmp->redir_type == OUT)
		*fd = open(tmp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (tmp->redir_type == APPEND)
		*fd = open(tmp->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd == -1)
		return (perror(tmp->file), GENERAL_ERROR);
	return (0);
}

int	open_files(t_node *node, int *in_fd, int *out_fd)
{
	t_redir_token	*tmp;
	int				ret;

	ret = 0;
	tmp = node->cmd.redir_token;
	while (tmp)
	{
		if (tmp->redir_type == HEREDOC)
			*in_fd = node->cmd.heredoc_fd;
		else if (tmp->redir_type == IN)
			ret = open_in_out_append(in_fd, tmp);
		else
			ret = open_in_out_append(out_fd, tmp);
		if (ret)
			return (ret);
		tmp = tmp->next;
	}
	return (0);
}
