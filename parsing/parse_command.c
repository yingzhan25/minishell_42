/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:34:27 by jkubaev           #+#    #+#             */
/*   Updated: 2025/10/01 12:15:27 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * is_redirection checks if a given token type represents a redirection operator
 *
 * @param type : The token type to check.
 * @return     : 1 if the token is a redirection (<, >, <<, >>), 0 otherwise.
 *
 * Example usage:
 * - T_LESS  (<)    -> returns 1
 * - T_GREAT (>)    -> returns 1
 * - T_WORD  ("ls") -> returns 0
 */
static int	is_redirection(t_token_type type)
{
	return (type == T_LESS || type == T_GREAT || type == T_DLESS
		|| type == T_DGREAT);
}

/*
 * parse_command:
 * Parses a single command and its associated arguments and
 * redirections from the token list.
 * Parameters:
 *   - list: pointer to the current token pointer
 *   - exit_code: pointer to shell exit code (updated in case of syntax errors)
 * Returns: pointer to a newly created t_node representing
 * the command, or NULL on failure
 */
t_node	*parse_command(t_token **list, int *exit_code)
{
	t_node			*node;
	t_redir_token	*redir;

	node = create_node(COMMAND);
	if (!node)
		return (NULL);
	while ((*list) && (*list)->type != T_PIPE && (*list)->type != T_EOF)
	{
		while ((*list)->type == T_WORD \
			&& (*list)->value && ((*list)->value[0] == 0))
			(*list) = (*list)->next;
		if ((*list)->type == T_WORD)
		{
			if (add_arg(node, &(*list)))
				return (free_ast(node), NULL);
		}
		else if (is_redirection((*list)->type))
		{
			redir = parse_redirection(&(*list), &(*exit_code));
			if (!redir)
				return (free_ast(node), NULL);
			add_redir(node, redir);
		}
	}
	return (node);
}
