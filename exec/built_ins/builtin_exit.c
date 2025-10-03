/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:58:36 by jkubaev           #+#    #+#             */
/*   Updated: 2025/10/01 12:12:51 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	* validate_exit_arg function checks whether the argument --
	* given to the 'exit' command is valid.
	*
	* @param arg: The string argument provided to the 'exit' builtin.
	*
	* Behavior:
	* - Returns 1 if the argument is NULL or empty (no argument given).
	* - Skips an optional '+' or '-' sign at the beginning.
	* - If the string after the sign is empty → returns -1 (invalid).
	* - Iterates through each character:
	*     - If a non-digit character is found → prints an error
	*       "exit: `<arg>`: numeric argument required" and returns -1.
	* - Returns 0 if the argument is a valid numeric string.
	*
	* @return
	*   0   → argument is a valid number.
	*   1   → argument is missing (NULL or empty string).
	*  -1   → argument is invalid (not a number).
 */
static int	validate_exit_arg(char *arg)
{
	int	i;

	if (!arg || !arg[0])
		return (1);
	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (!arg[i])
		return (-1);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			ft_putstr_fd("exit: `", STDERR_FILENO);
			ft_putstr_fd(arg, STDERR_FILENO);
			ft_putstr_fd("`: numeric argument required\n", STDERR_FILENO);
			return (-1);
		}
		i++;
	}
	return (0);
}

/*
	* handle_exit_args function processes the argument -
	* passed to the 'exit' command
	* and determines the appropriate exit code.
	*
	* @param arg: The string argument provided to the 'exit' builtin.
	*
	* Behavior:
	* - First, it validates the argument using validate_exit_arg():
	*     - If the argument is invalid → returns -1.
	* - If valid, converts the string to a long integer using ft_atoi().
	* - Checks whether the converted value fits into -
	* the 32-bit signed integer range:
	*     - If it is greater than INT_MAX (2147483647) or -
	* less than INT_MIN (-2147483648),
	*       an error message is printed and -1 is returned.
	* - If everything is valid, returns the parsed exit code.
	*
	* @return
	*   long → the valid exit code value.
	*   -1   → if the argument is invalid or out of range.
 */
static long	handle_exit_args(char *arg)
{
	long	exit_code;

	exit_code = validate_exit_arg(arg);
	if (exit_code == -1)
		return (258);
	exit_code = ft_atoi(arg);
	if (exit_code > 2147483647 || exit_code < -2147483648)
	{
		ft_putstr_fd("exit: `", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("`: numeric argument required\n", STDERR_FILENO);
		return (258);
	}
	return (exit_code);
}

/*
	* builtin_exit function implements the 'exit' builtin command.
	*
	* @param shell: Pointer to the shell structure containing state
	and resources.
	* @param cmd:   Command arguments (e.g., ["exit", "42"]).
	*
	* Behavior:
	* - Prints "exit" to the terminal.
	* - If too many arguments are given (>= 3), prints an error and returns 1
	*   without exiting the shell.
	* - If one argument is provided:
	*     - Uses handle_exit_args() to validate and parse it.
	*     - If invalid, sets exit_code = 2 (as per bash behavior).
	* - Normalizes exit_code to the range [0, 255] (mod 256).
	* - Frees allocated resources (AST, input, environment, etc.).
	* - Clears readline history.
	* - Terminates the process with exit(exit_code).
	*
	* @return
	*   0 → Only reached if exit() is not called (for safety).
 */
int	builtin_exit(t_shell *shell, char **cmd)
{
	int	count;
	int	exit_code;

	count = count_arguments(cmd);
	exit_code = shell->exit_code;
	printf("exit\n");
	if (count >= 3)
		return (ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO), 1);
	if (count == 2)
		exit_code = handle_exit_args(*(cmd + 1));
	if (exit_code > 256)
		exit_code = exit_code % 256;
	free_ast(shell->nodes);
	free(shell->input);
	clean_shell(shell);
	rl_clear_history();
	exit(exit_code);
	return (0);
}
