/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:15:26 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/30 17:57:09 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * append_env_list:
 *  Appends a new node to the environment variable linked list.
 *
 * Parameters:
 *  - head: pointer to the head of the list
 *  - tail: pointer to the tail of the list
 *  - new_node: new environment node to append
 *
 * Notes:
 *  - Updates both head and tail pointers accordingly
 */
void	append_env_list(t_env **head, t_env **tail, t_env *new_node)
{
	if (!*head)
	{
		*head = new_node;
		*tail = new_node;
	}
	else
	{
		(*tail)->next = new_node;
		*tail = new_node;
	}
}

/*
 * new_list_f:
 *  Creates a new environment variable node with given name and value.
 *
 * Parameters:
 *  - name: environment variable name (already allocated)
 *  - value: environment variable value (already allocated)
 *
 * Returns:
 *  - Pointer to the newly created node
 *  - NULL on allocation failure
 *
 * Notes:
 *  - Does not duplicate strings; assumes ownership of name and value
 */
t_env	*new_list_f(char *name, char *value)
{
	t_env	*new_list;

	new_list = malloc(sizeof(t_env));
	if (!new_list)
		return (NULL);
	new_list->name = name;
	new_list->value = value;
	new_list->equal_sign = 1;
	new_list->next = NULL;
	return (new_list);
}

/*
 * parse_and_create_env_list:
 *  Parses a single "NAME=VALUE" string and creates an environment node.
 *
 * Parameters:
 *  - envp: string in the format "NAME=VALUE"
 *
 * Returns:
 *  - Pointer to newly allocated t_env node
 *  - NULL on failure (invalid format or allocation error)
 *
 * Notes:
 *  - Allocates new strings for name and value
 */
t_env	*parse_and_create_env_list(const char *envp)
{
	t_env	*new_list;
	char	*name;
	char	*value;
	char	*equal_sign;

	equal_sign = ft_strchr(envp, '=');
	if (!equal_sign)
		return (NULL);
	name = ft_substr(envp, 0, equal_sign - envp);
	if (!name)
		return (NULL);
	value = ft_strdup(equal_sign + 1);
	if (!value)
		return (free(name), NULL);
	new_list = new_list_f(name, value);
	if (!new_list)
		return (free(name), free(value), NULL);
	return (new_list);
}

/*
 * init_envp_list:
 *  Converts an array of strings (envp) into a linked list 
 * of environment variables.
 *
 * Parameters:
 *  - envp: NULL-terminated array of "NAME=VALUE" strings
 *
 * Returns:
 *  - Pointer to the head of the linked list
 *  - NULL on failure
 *
 * Notes:
 *  - Frees all previously allocated nodes on failure
 *  - Maintains order of variables as in the original envp array
 */
t_env	*init_envp_list(char **envp)
{
	t_env	*new_list;
	t_env	*head;
	t_env	*tail;
	int		i;

	i = 0;
	new_list = NULL;
	head = NULL;
	tail = NULL;
	while (envp[i])
	{
		new_list = parse_and_create_env_list(envp[i]);
		if (!new_list)
			return (free_env_list(head), NULL);
		append_env_list(&head, &tail, new_list);
		i++;
	}
	return (head);
}

/*
 * init_envp:
 *  Initializes the t_shell structure and populates 
 * its environment variable list.
 *
 * Parameters:
 *  - envp: NULL-terminated array of "NAME=VALUE" strings
 *
 * Returns:
 *  - Pointer to the initialized t_shell structure
 *  - NULL on allocation failure
 *
 * Notes:
 *  - Sets default values for exit_code, input, and nodes
 */
t_shell	*init_envp(char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env_list = init_envp_list(envp);
	if (!shell->env_list)
		return (free(shell), NULL);
	shell->exit_code = 0;
	shell->input = NULL;
	shell->nodes = NULL;
	return (shell);
}
