/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:58:25 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/30 15:14:59 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	* ft_print_cmd function prints command arguments for the 'echo' builtin.
	*
	* @param cmd: Array of command arguments.
	* @param i:   Pointer to the current index in the array.
	*
	* Behavior:
	* - Prints each argument followed by a space.
	* - Stops printing before the last argument (handled outside).
	*
	* Used inside the 'echo' builtin to display user-provided text.
 */
static void	ft_print_cmd(char **cmd, int *i)
{
	while (cmd[*i] && (cmd[*i + 1] != NULL))
	{
		printf("%s ", cmd[*i]);
		(*i)++;
	}
}

static int	is_valid_n_arg(char *arg)
{
	if (*arg == '-')
		arg++;
	else
		return (1);
	while (*arg)
	{
		if (*arg != 'n')
			return (1);
		arg++;
	}
	return (0);
}

int	builtin_echo(t_shell *shell, char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i] && !is_valid_n_arg(cmd[i]))
		i++;
	if (i != 1)
	{
		ft_print_cmd(cmd, &i);
		if (cmd[i])
			printf("%s", cmd[i]);
		else
			write(1, "", 1);
	}
	else
	{
		ft_print_cmd(cmd, &i);
		if (cmd[i])
			printf("%s\n", cmd[i]);
		else
			write(1, "\n", 1);
	}
	shell->exit_code = 0;
	return (0);
}
