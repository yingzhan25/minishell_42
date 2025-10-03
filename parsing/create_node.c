/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:23:34 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/29 10:48:24 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * create_node allocates and initializes a new AST node.
 *
 * @param type : The type of the node (e.g., PIPE, COMMAND).
 * @return     : Pointer to the newly created node, or NULL if allocation fails.
 *
 * The node is initialized as follows:
 * - For PIPE nodes: left and right pointers are set to NULL.
 * - For COMMAND nodes: command array and redirection list are set to NULL,
 *   heredoc file descriptor is set to -1.
 *
 * Example usage:
 * t_node *node = create_node(COMMAND);
 * if (!node)
 *     handle_error();
 */
t_node	*create_node(t_node_type type)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (printf(ALLOCATION_FAIL), NULL);
	node->type = type;
	node->pipe.left = NULL;
	node->pipe.right = NULL;
	node->cmd.redir_token = NULL;
	node->cmd.cmd = NULL;
	node->cmd.heredoc_fd = -1;
	return (node);
}
