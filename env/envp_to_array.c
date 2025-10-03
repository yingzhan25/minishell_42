/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_to_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:00:03 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/29 11:52:17 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * count_envp_list:
 *  Counts the number of nodes in the linked list of environment variables.
 *
 * Parameters:
 *  - env_list: pointer to the head of the environment variable linked list
 *
 * Returns:
 *  - Number of environment variable nodes in the list
 */
int	count_envp_list(t_env *env_list)
{
	t_env	*current;
	int		count;

	count = 0;
	current = env_list;
	while (current)
	{
		current = current->next;
		count++;
	}
	return (count);
}

/*
 * env_string:
 *  Creates a single string in the format "NAME=VALUE" from given name and value
 *
 * Parameters:
 *  - name: environment variable name
 *  - value: environment variable value
 *
 * Returns:
 *  - Newly allocated string "NAME=VALUE"
 *  - NULL on allocation failure
 *
 * Notes:
 *  - Properly frees temporary allocations to avoid memory leaks
 */
char	*env_string(char *name, char *value)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin_g(name, "=");
	if (!temp)
		return (NULL);
	result = ft_strjoin_g(temp, value);
	if (!result)
		return (free(temp), NULL);
	return (free(temp), result);
}

/*
 * fill_array:
 *  Fills a pre-allocated array of strings with "NAME=VALUE" strings
 *  from the environment linked list.
 *
 * Parameters:
 *  - arr: pre-allocated array of char pointers
 *  - env_list: head of the environment variable linked list
 *
 * Returns:
 *  - 0 on success
 *  - 1 on allocation failure
 *
 * Notes:
 *  - Sets the last element of the array to NULL
 */
int	fill_array(char **arr, t_env *env_list)
{
	t_env	*current;
	int		i;

	i = 0;
	current = env_list;
	while (current)
	{
		arr[i] = env_string(current->name, current->value);
		if (!arr[i])
			return (1);
		current = current->next;
		i++;
	}
	arr[i] = NULL;
	return (0);
}

/*
 * envp_to_array:
 *  Converts the linked list of environment variables to a NULL-terminated
 *  array of strings suitable for execve and similar functions.
 *
 * Parameters:
 *  - env_list: head of the environment variable linked list
 *
 * Returns:
 *  - Newly allocated array of strings "NAME=VALUE"
 *  - NULL on failure
 *
 * Notes:
 *  - Uses count_envp_list to allocate the correct size
 *  - Frees partially allocated arrays if fill_array fails
 */
char	**envp_to_array(t_env *env_list)
{
	char	**arr;
	int		count;

	count = count_envp_list(env_list);
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	if (fill_array(arr, env_list))
		return (clean_array(arr), NULL);
	return (arr);
}
