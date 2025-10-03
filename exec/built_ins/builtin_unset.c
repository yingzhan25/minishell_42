/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 16:12:01 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/29 10:21:39 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	* remove_node function removes a specific node from a linked list of
	* environment variables and frees its memory.
	*
	* @param head: Pointer to the head of the linked list.
	* @param node_for_remove: Pointer to the node that should be removed.
	*
	* Behavior:
	* - Checks if the node to remove is the head:
	*     - If yes, updates the head to the next node and frees the old head.
	* - Otherwise, iterates through the list to find the node:
	*     - Updates the previous node's next pointer to skip the removed node.
	*     - Frees the removed node's name, value, and the node itself.
	* - Does nothing if the node is not found.
 */
void	remove_node(t_env **head, t_env *node_for_remove)
{
	t_env	*tmp;
	t_env	*previous;

	tmp = *head;
	if (tmp != NULL && tmp == node_for_remove)
	{
		*head = tmp->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
		return ;
	}
	while (tmp != NULL && tmp != node_for_remove)
	{
		previous = tmp;
		tmp = tmp->next;
	}
	if (tmp != NULL)
	{
		previous->next = tmp->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}

/*
	* builtin_unset function implements the 'unset' shell builtin.
	*
	* @param shell: Pointer to the shell structure containing 
	* environment variables.
	* @param cmd: Array of command arguments; cmd[1..n] are 
	* variable names to remove.
	*
	* Behavior:
	* - Loops through each variable name in cmd starting from index 1.
	* - Uses is_env_exist() to check if the environment variable exists.
	* - If the variable exists, remove_node() deletes it from 
	* the linked list and frees memory.
	* - Returns 0 as the exit status.
	*
	* @return
	*   int → Exit status of the command (always 0).
 */
int	builtin_unset(t_shell *shell, char **cmd)
{
	int		exit_status;
	int		i;
	t_env	*existing;

	exit_status = 0;
	i = 1;
	existing = NULL;
	while (cmd[i])
	{
		existing = is_env_exist(shell->env_list, cmd[i]);
		if (existing)
			remove_node(&(shell->env_list), existing);
		i++;
	}
	return (exit_status);
}
