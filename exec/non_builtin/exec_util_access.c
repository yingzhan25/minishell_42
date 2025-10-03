/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util_access.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 10:38:08 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/28 21:00:41 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_access(char *path)
{
	struct stat	statbuf;

	if (!lstat(path, &statbuf))
	{
		if (!S_ISDIR(statbuf.st_mode) && !access(path, X_OK))
			return (0);
	}
	return (1);
}

void	check_dir_cmd(char *path, int *flag)
{
	struct stat	statbuf;

	if (lstat(path, &statbuf) == -1)
	{
		if (errno == EACCES)
			*flag = 1;
		return ;
	}
	if (errno == EACCES)
		*flag = 1;
}

int	check_dir_path(char *path, int *flag)
{
	struct stat	statbuf;

	if (lstat(path, &statbuf) == -1)
	{
		if (errno == EACCES)
			*flag = 1;
		else if (errno == ENOENT)
			*flag = 0;
		else if (errno == ENOTDIR)
			*flag = 3;
		return (1);
	}
	if (S_ISDIR(statbuf.st_mode))
		return (0);
	if (errno == EACCES)
		*flag = 1;
	return (1);
}

int	print_error_cmd(int flag, char *cmd_name)
{
	if (flag == 1)
		return (ft_putstr_fd(cmd_name, STDERR_FILENO), \
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO), \
		COMMAND_NOT_EXECUTABLE);
	else
		return (ft_putstr_fd(cmd_name, STDERR_FILENO), \
		ft_putstr_fd(": command not found\n", STDERR_FILENO), \
		COMMAND_NOT_FOUND);
}

int	print_error_path(int flag, char *cmd_name)
{
	if (flag == 1)
		return (ft_putstr_fd(cmd_name, STDERR_FILENO), \
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO), \
		COMMAND_NOT_EXECUTABLE);
	else if (flag == 2)
		return (ft_putstr_fd(cmd_name, STDERR_FILENO), \
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO), \
		COMMAND_NOT_EXECUTABLE);
	else if (flag == 3)
		return (ft_putstr_fd(cmd_name, STDERR_FILENO), \
		ft_putstr_fd(": Not a directory\n", STDERR_FILENO), \
		COMMAND_NOT_EXECUTABLE);
	else
		return (ft_putstr_fd(cmd_name, STDERR_FILENO), \
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO), \
		COMMAND_NOT_FOUND);
}

/**
 * For cmd name:
 * 0: command not found
 * 1: Permission denied
 *
 * For cmd with full path:
 * 0: No such file or directory
 * 1: Permission denied
 * 2: Is a directory(e.g. $PWD)
 * 3: Not a directory(take file as directory, e.g. /etc/passwd/subdir)
 */