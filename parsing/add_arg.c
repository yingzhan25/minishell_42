/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:27:49 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/29 11:42:36 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * ensure_cmd_capacity:
 *  Ensures that the command node's argument array has 
 * enough space to add a new argument.
 *
 * Parameters:
 *  - cmd: pointer to the command node
 *  - count: current number of arguments in the command
 *
 * Returns:
 *  - 0 on success
 *  - 1 if memory allocation fails
 *
 * Notes:
 *  - If the command node's array is NULL, it initializes 
 * it with space for 2 pointers.
 *  - Otherwise, it reallocates the array to hold one additional argument.
 *  - Uses ft_realloc1 to handle memory resizing.
 */
static int	ensure_cmd_capacity(t_node *cmd, int count)
{
	if (!cmd->cmd.cmd)
	{
		cmd->cmd.cmd = (char **)malloc(sizeof(char *) * 2);
		if (!cmd->cmd.cmd)
			return (printf(ALLOCATION_FAIL), 1);
	}
	else
	{
		cmd->cmd.cmd = ft_realloc1(cmd->cmd.cmd,
				(count + 1) * sizeof(char *),
				(count + 2) * sizeof(char *));
		if (!cmd->cmd.cmd)
			return (printf(ALLOCATION_FAIL), 1);
	}
	return (0);
}

/*
 * add_arg:
 *  Adds the current token's value as an argument to the command node.
 *
 * Parameters:
 *  - cmd: pointer to the command node
 *  - list: pointer to the current token in the token list
 *
 * Returns:
 *  - 0 on success
 *  - 1 if memory allocation fails
 *
 * Behavior:
 *  - Determines the current number of arguments in the command.
 *  - Ensures there is enough capacity in the argument 
 * array using ensure_cmd_capacity().
 *  - Copies the token's value into the command's argument array.
 *    - If the token's value is NULL, an empty string is used.
 *  - Updates the argument array's NULL terminator.
 *  - Advances the token list pointer to the next token.
 *
 * Notes:
 *  - Handles memory allocation errors gracefully by 
 * returning 1 and printing an error message.
 */
int	add_arg(t_node *cmd, t_token **list)
{
	int	i;

	i = 0;
	while (cmd->cmd.cmd && cmd->cmd.cmd[i])
		i++;
	if (ensure_cmd_capacity(cmd, i))
		return (1);
	if (!(*list)->value)
		cmd->cmd.cmd[i] = ft_strdup("");
	else
	{
		cmd->cmd.cmd[i] = ft_strdup((*list)->value);
		if (!cmd->cmd.cmd[i])
			return (printf(ALLOCATION_FAIL), 1);
	}
	cmd->cmd.cmd[i + 1] = NULL;
	*list = (*list)->next;
	return (0);
}
