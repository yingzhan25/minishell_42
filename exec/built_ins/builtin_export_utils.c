/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 15:24:18 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/30 18:20:39 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	* is_first_char_valid function checks if a character is valid as the first
	* character of a shell variable name.
	*
	* @param c: Character to check.
	*
	* Behavior:
	* - Returns true (non-zero) if the character is:
	*     - A lowercase letter ('a'–'z')
	*     - An uppercase letter ('A'–'Z')
	*     - An underscore ('_')
	* - Returns false (0) otherwise.
	*
	* @return
	*   int → 1 if valid first character, 0 if invalid.
 */
int	is_first_char_valid(char c)
{
	return (('a' <= c && 'z' >= c) || ('A' <= c && 'Z' >= c) || (c == '_'));
}

/*
	* is_valid_identifier function checks if a given string is a valid
	* shell variable name for use with export.
	*
	* @param name: The variable name to validate.
	*
	* Behavior:
	* - First character must be a letter or underscore 
	* (checked via is_first_char_valid()).
	* - Iterates through the rest of the string:
	*     - If a '-' character is found, the identifier is invalid.
	*     - If a '=' character is found before any invalid 
	* character, it's considered valid.
	* - Returns 0 if the identifier is valid, 1 if invalid.
	*
	* @return
	*   int → 0  : valid identifier.
	*         1  : invalid identifier.
 */
int	is_valid_identifier(char *name)
{
	int	i;
	int	valid;

	i = 0;
	valid = 0;
	if (!is_first_char_valid(name[i]))
		return (1);
	i++;
	while (name[i])
	{
		if (name[i] == '-')
		{
			valid = 1;
			break ;
		}
		if (name[i] == '=')
		{
			valid = 0;
			break ;
		}
		i++;
	}
	return (valid);
}

/*
	* parse_export_arg function splits a string in the form "NAME=VALUE"
	* into separate name and value strings.
	*
	* @param arg:   Input string containing the variable assignment.
	* @param name:  Pointer to store the duplicated variable name.
	* @param value: Pointer to store the duplicated variable value.
	*
	* Behavior:
	* - Searches for the '=' character in the input string.
	*     - If '=' is not found:
	*         - The entire string is treated as the variable name.
	*         - The value is set to an empty string "".
	*     - If '=' is found:
	*         - Characters before '=' are duplicated as the name.
	*         - Characters after '=' are duplicated as the value.
	* - Both name and value are dynamically allocated (caller must free them).
 */
void	parse_export_arg(char *arg, char **name, char **value, int *equal_s)
{
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
	{
		*name = ft_strdup(arg);
		*value = ft_strdup("");
	}
	else
	{
		*name = ft_substr(arg, 0, equal_sign - arg);
		*value = ft_strdup(equal_sign + 1);
		*equal_s = 1;
	}
}

/*
	* is_env_exist function checks if an environment variable with a given
	* name already exists in the linked list.
	*
	* @param list: Pointer to the head of the environment variable linked list.
	* @param name: Name of the variable to search for.
	*
	* Behavior:
	* - Iterates through the linked list of t_env nodes.
	* - Compares each node's name with the given name using ft_strncmp().
	* - If a matching node is found, returns a pointer to that node.
	* - If no match is found, returns NULL.
	*
	* @return
	*   t_env* → Pointer to the existing environment variable node, 
	* or NULL if not found.
 */
t_env	*is_env_exist(t_env *list, char *name)
{
	t_env	*tmp;

	tmp = list;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name, ft_strlen(name)))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

/**
 * print_env_vars - Prints all environment variables with export format
 * @env_list: Linked list of environment variables
 *
 * This function displays all environment variables in the format:
 * declare -x NAME="VALUE"
 * This matches bash's behavior when 'export' is called without arguments
 */
void	print_env_vars(t_env *env_list)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(current->name, STDOUT_FILENO);
		if (!current->equal_sign)
		{
			ft_putstr_fd("\n", STDOUT_FILENO);
			current = current->next;
			continue ;
		}
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(current->value, STDOUT_FILENO);
		ft_putstr_fd("\"\n", STDOUT_FILENO);
		current = current->next;
	}
}
