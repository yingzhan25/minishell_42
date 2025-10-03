/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util_clean.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:27:24 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/28 10:38:33 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clean_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	close_heredoc_fd(t_node *node)
{
	if (node->cmd.heredoc_fd == -1)
		return ;
	if (node->cmd.heredoc_fd)
		close(node->cmd.heredoc_fd);
}

void	close_fd(int in_fd, int out_fd)
{
	if (in_fd > 2)
		close(in_fd);
	if (out_fd > 2)
		close(out_fd);
}
