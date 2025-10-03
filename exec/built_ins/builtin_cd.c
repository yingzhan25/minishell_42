/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 12:50:16 by jkubaev           #+#    #+#             */
/*   Updated: 2025/10/01 12:13:09 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	* go_home - changes directory to the user's HOME
	* @shell: pointer to the main shell structure containing env variables
	*
	* Description:
	*   Looks up the HOME environment variable and tries to change
	*   the current working directory to that path.
	*
	* Return:
	*   0  on success
	*   1  on error (HOME not set or chdir failed)
*/
static int	go_home(t_shell *shell)
{
	char	*home;

	home = get_env_value(shell, "HOME");
	if (!home)
		return (1);
	if (chdir(home) == -1)
		return (perror("cd"), 1);
	return (0);
}

/*
	* change_directory function changes the current working directory
	* to the given path.
	*
	* @param arg: The target directory path to change into.
	*
	* @return 0 on success,
	*         1 on failure (and prints an error using perror).
*/
static int	change_directory(char *arg)
{
	if (chdir(arg) == -1)
		return (perror("cd"), 1);
	return (0);
}

/*
	* update_env_value function updates the values of PWD and OLDPWD
	* environment variables in the shell's environment list.
	*
	* @param shell:   The main shell structure containing the environment list.
	* @param oldpwd:  The previous working directory path to set as OLDPWD.
	* @param pwd:     The new current working directory path to set as PWD.
	*
	* This function iterates through the environment list and updates
	* the values of "PWD" and "OLDPWD" if they exist.
*/
static void	update_env_value(t_shell *shell, char *oldpwd, char *pwd)
{
	t_env	*current;

	current = shell->env_list;
	while (current)
	{
		if (ft_strcmp(current->name, "PWD") == 0)
		{
			free(current->value);
			current->value = ft_strdup(pwd);
		}
		else if (ft_strcmp(current->name, "OLDPWD") == 0)
		{
			free(current->value);
			current->value = ft_strdup(oldpwd);
		}
		current = current->next;
	}
}

/*
	* builtin_cd function implements the 'cd' builtin command.
	*
	* @param shell: The main shell structure containing environment variables.
	* @param cmd:   The array of command arguments passed to 'cd'.
	*
	* Behavior:
	* - If more than one argument is given, it prints an error.
	* - If no argument is provided, it tries to change to the user's HOME
	directory.
	* - If one argument is provided, it attempts to change to that directory.
	* - Updates PWD and OLDPWD environment variables after a successful change.
	*
	* @return 0 on success, 1 on failure.
 */
int	builtin_cd(t_shell *shell, char **cmd)
{
	int		argc;
	char	pwd[4096];
	char	oldpwd[4096];

	argc = count_arguments(cmd + 1);
	if (argc == 0 && go_home(shell))
		return (1);
	if (argc > 1)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (!getcwd(oldpwd, sizeof(pwd)))
		return (perror("getcwd() error"), 1);
	if (argc == 1 && change_directory(cmd[1]))
		return (1);
	if (!getcwd(pwd, sizeof(pwd)))
		return (perror("getcwd() error"), 1);
	update_env_value(shell, oldpwd, pwd);
	return (0);
}
