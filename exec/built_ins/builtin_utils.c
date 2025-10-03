/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:01:55 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/30 17:48:11 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	* print_envp function prints all environment 
	* variables to the standard output.
	*
	* @param shell: Pointer to the head of the linked list containing 
	* environment variables.
	*
	* Behavior:
	* - Iterates through the linked list of t_env nodes.
	* - For each node, prints "name=value" followed by a newline.
	* - Uses ft_putstr_fd() to print to STDOUT.
	*
	* @return
	*   void
 */
void	print_envp(t_env *shell)
{
	t_env	*current;

	current = shell;
	while (current)
	{
		if (!current->equal_sign)
		{
			current = current->next;
			continue ;
		}
		ft_putstr_fd(current->name, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putstr_fd(current->value, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		current = current->next;
	}
}

/*
	* count_arguments function counts the number of arguments in a command array
	*
	* @param cmd: Null-terminated array of strings representing
	* command and its arguments.
	*
	* Behavior:
	* - Iterates through the array until it encounters a NULL pointer.
	* - Increments a counter for each non-NULL element.
	*
	* @return
	*   int → Number of arguments in the cmd array.
 */
int	count_arguments(char **cmd)
{
	int	count;

	count = 0;
	while (cmd[count])
		count++;
	return (count);
}
