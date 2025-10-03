/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:31:54 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/29 10:58:19 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * add_redir:
 *  Adds a redirection token to the given command node.
 *
 * Parameters:
 *  - cmd_node: pointer to the command node
 *  - redir: pointer to the redirection token to be added
 *
 * Notes:
 *  - If the command node has no existing redirections, 
 * the new redirection becomes the first.
 *  - Otherwise, the new redirection is appended to the 
 * end of the redirection linked list.
 */
void	add_redir(t_node *cmd_node, t_redir_token *redir)
{
	t_redir_token	*current;

	if (!cmd_node->cmd.redir_token)
		cmd_node->cmd.redir_token = redir;
	else
	{
		current = cmd_node->cmd.redir_token;
		while (current->next)
			current = current->next;
		current->next = redir;
	}
}
