/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 11:37:01 by jkubaev           #+#    #+#             */
/*   Updated: 2025/10/01 12:13:49 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	* create_env function creates a new environment variable node
	* to be stored in the shell's environment linked list.
	*
	* @param name1: The name of the environment variable (e.g., "PATH").
	* @param value: The value of the environment variable (e.g., "/usr/bin").
	*
	* Behavior:
	* - Allocates memory for a new t_env struct.
	* - Duplicates the given name and value strings into the struct fields.
	* - Sets the next pointer to NULL (as it will be linked later).
	* - If allocation or duplication fails at any step, already-allocated
	*   memory is freed and NULL is returned.
	*
	* @return
	*   Pointer to a newly created t_env struct → success.
	*   NULL → if memory allocation fails.
 */
t_env	*create_env(char *name1, char *value, int equal_sign)
{
	t_env	*new_ist;

	new_ist = malloc(sizeof(t_env));
	if (!new_ist)
	{
		return (NULL);
	}
	new_ist->name = ft_strdup(name1);
	if (!new_ist->name)
		return (free(new_ist), NULL);
	new_ist->value = ft_strdup(value);
	if (!new_ist->value)
		return (free(new_ist->name), free(new_ist), NULL);
	new_ist->equal_sign = equal_sign;
	new_ist->next = NULL;
	return (new_ist);
}

/*
	* add_env function adds a new environment --
	* variable to the end of the linked list.
	*
	* @param list:  Pointer to the head of the environment variable linked list.
	* @param name:  Name of the environment variable to add.
	* @param value: Value of the environment variable to add.
	*
	* Behavior:
	* - Creates a new t_env node using create_env().
	* - If the list is empty (NULL), it attempts to set the head to the new node
	*   and returns -1 (caller should handle updating the head).
	* - Otherwise, traverses to the end of the list and appends the new node.
	*
	* @return
	*   0  → success, added to the end of the list.
	*  -1  → list was originally NULL (caller should update the head).
 */
int	add_env(t_env *list, char *name, char *value, int equal_sign)
{
	t_env	*new_list;
	t_env	*current;

	new_list = create_env(name, value, equal_sign);
	if (list == NULL)
	{
		list = new_list;
		return (-1);
	}
	current = list;
	while (current->next != NULL)
		current = current->next;
	current->next = new_list;
	return (0);
}

/*
 * update_env_value function updates the value  --
 * of an existing environment variable node.
 *
 * @param node:  Pointer to the t_env node to update.
 * @param value: New value to assign to the environment variable.
 *
 * Behavior:
 * - Duplicates the new value string.
 * - If duplication fails, returns 1 (failure).
 * - Frees the old value string stored in the node.
 * - Assigns the duplicated string as the new value.
 *
 * @return
 *   0 → success, value updated.
 *   1 → memory allocation failed.
 */
static int	update_env_value(t_env *node, char *value, int equal_sign)
{
	char	*new_value;

	new_value = ft_strdup(value);
	if (!new_value)
		return (1);
	free(node->value);
	node->value = new_value;
	node->equal_sign = equal_sign;
	return (0);
}

/*
	* update_or_add_env function updates the value of an
	* existing environment variable
	* or adds a new variable if it does not exist.
	*
	* @param list: Pointer to the head of the environment variable linked list.
	* @param idf:  String representing the variable in "NAME=VALUE" format.
	*
	* Behavior:
	* - Parses the input string into a variable name and value
	* using parse_export_arg().
	* - If parsing fails (name or value is NULL), returns -1.
	* - Checks if the variable already exists in the list with is_env_exist().
	*     - If it exists, updates its value using update_env_value().
	*     - If it does not exist, adds a new node using add_env().
	*
	* @return
	*   0  → success (updated or added variable).
	*  -1  → parsing failed or memory allocation failed.
 */
int	update_or_add_env(t_env *list, char	*idf)
{
	char	*name;
	char	*value;
	int		equal_sign;
	t_env	*existing;

	equal_sign = 0;
	parse_export_arg(idf, &name, &value, &equal_sign);
	if (!name || !value)
		return (-1);
	existing = is_env_exist(list, name);
	if (!existing)
	{
		if (add_env(list, name, value, equal_sign))
			return (free(name), free(value), -1);
		else
			return (free(name), free(value), 0);
	}
	else
	{
		if (update_env_value(existing, value, equal_sign))
			return (free(name), free(value), -1);
		else
			return (free(name), free(value), 0);
	}
}

/*
	* builtin_export function implements the 'export' builtin command.
	*
	* @param shell: Pointer to the shell structure
	* containing the environment list.
	* @param cmd:   Command arguments (e.g.,
	* ["export", "VAR=value", "NAME=VAL"]).
	*
	* Behavior:
	* - If no arguments are provided, prints the current environment variables.
	* - Iterates over each argument starting from index 1:
	*     - Checks if the argument is a valid identifier
	* using is_valid_identifier():
	*         - If invalid, prints an error message to STDERR
	* and sets exit_status = 1.
	*     - If valid, updates the existing environment
	* variable or adds a new one
	*       using update_or_add_env().
	* - Returns the exit status:
	*     - 0 → all identifiers were valid and successfully added/updated.
	*     - 1 → at least one invalid identifier or memory allocation failure.
	*
	* @return
	*   int → exit status of the builtin command.
 */
int	builtin_export(t_shell *shell, char **cmd)
{
	int	i;
	int	exit_status;

	exit_status = 0;
	i = 1;
	if (!cmd[i])
		return (print_env_vars(shell->env_list), exit_status);
	while (cmd[i])
	{
		if (is_valid_identifier(cmd[i]))
		{
			ft_putstr_fd("export: `", STDERR_FILENO);
			ft_putstr_fd(cmd[i], STDERR_FILENO);
			ft_putstr_fd("`: not a valid identifier\n", STDERR_FILENO);
			exit_status = 1;
		}
		else if (update_or_add_env(shell->env_list, cmd[i]) == -1)
			return (printf("Memory fail\n"), 1);
		i++;
	}
	return (exit_status);
}
