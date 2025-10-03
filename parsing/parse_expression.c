/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expression.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:35:27 by jkubaev           #+#    #+#             */
/*   Updated: 2025/10/01 12:17:11 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * validate_pipe_syntax checks if the pipe is correctly placed in the token list
 * Returns 1 on syntax error, 0 otherwise.
 */
static int	validate_pipe_syntax(t_token *list, t_node *root, int *exit_code)
{
	if (!root || !list || list->type == T_PIPE || list->type == T_EOF)
	{
		*exit_code = 2;
		ft_putstr_fd("minishell:", STDOUT_FILENO);
		ft_putstr_fd(" syntax error near unexpected token `", STDERR_FILENO);
		ft_putstr_fd(list->value, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
		free_ast(root);
		return (1);
	}
	return (0);
}

/*
 * create_pipe_node allocates a PIPE node and assigns the left branch.
 * Frees left if allocation fails.
 */
static t_node	*create_pipe_node(t_node *left)
{
	t_node	*node;

	node = create_node(PIPE);
	if (!node)
		return (free_ast(left), NULL);
	node->pipe.left = left;
	return (node);
}

/*
 * parse_right_pipe_branch parses the right side of a PIPE node.
 * Returns 1 on failure, 0 on success.
 */
static int	parse_right_pipe_branch(t_node *pipe, t_token **list, \
	int *exit_code)
{
	pipe->pipe.right = parse_expression(list, exit_code);
	if (!(pipe->pipe.right))
	{
		free_ast(pipe->pipe.left);
		free(pipe);
		return (1);
	}
	return (0);
}

/*
 * handle_the_pipe validates, creates, and parses right branch for a pipe.
 * Returns the new PIPE node or NULL on error.
 */
static t_node	*handle_the_pipe(t_node *root, t_token	**list, int *exit_code)
{
	t_node	*node;

	if (validate_pipe_syntax((*list)->next, root, exit_code))
		return (NULL);
	node = create_pipe_node(root);
	*list = (*list)->next;
	if (parse_right_pipe_branch(node, list, exit_code))
		return (NULL);
	return (node);
}

/*
 * parse_expression parses a command or a pipeline from a list of tokens.
 * Returns the root node of the AST, or NULL if parsing fails.
 */
t_node	*parse_expression(t_token **list, int *exit_code)
{
	t_node	*root;
	t_token	*tmp;

	tmp = *list;
	root = NULL;
	if (tmp && (tmp)->type == T_EOF)
		return (NULL);
	if (tmp && !((tmp)->type == T_PIPE))
	{
		root = parse_command(&tmp, exit_code);
		if (!root)
			return (NULL);
	}
	if (tmp && (tmp)->type == T_PIPE)
		root = handle_the_pipe(root, &tmp, exit_code);
	return (root);
}
