/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 10:35:16 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/28 18:48:53 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*Only cmd_name: need concat all dirs in path with the name;
check as many times as loop;
once found break immediately;
if not found, print error msg at end*/
static int	concat_path(char *cmd_name, char **dirs, char **path)
{
	int		i;
	int		flag;
	char	*tmp;

	i = -1;
	flag = 0;
	while (dirs[++i])
	{
		*path = ft_strjoin(dirs[i], "/");
		if (!*path)
			return (perror("Malloc"), GENERAL_ERROR);
		tmp = ft_strjoin(*path, cmd_name);
		if (!tmp)
			return (free(*path), perror("Malloc"), GENERAL_ERROR);
		free(*path);
		*path = tmp;
		if (!check_access(*path))
			return (0);
		check_dir_cmd(*path, &flag);
		free(*path);
	}
	return (print_error_cmd(flag, cmd_name));
}

/*Full path cmd: check only once*/
static int	check_full_path(char *cmd_path, char **path)
{
	int	flag;

	flag = 0;
	if (!check_access(cmd_path))
	{
		*path = cmd_path;
		return (0);
	}
	if (!check_dir_path(cmd_path, &flag))
		flag = 2;
	return (print_error_path(flag, cmd_path));
}

/*Check cmd with full path or only cmd_name;
check path_env, esp. PATH can be unset*/
int	find_cmd_path(char **cmd, char **path, t_shell *shell)
{
	char	*path_env;
	char	**dirs;
	int		ret;

	if (ft_strchr(cmd[0], '/'))
		return (check_full_path(cmd[0], path));
	path_env = get_env_value(shell, "PATH");
	if (!path_env)
		return (ft_putstr_fd(cmd[0], STDERR_FILENO), \
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO), \
		COMMAND_NOT_FOUND);
	dirs = ft_split(path_env, ':');
	if (!dirs)
		return (ft_putstr_fd("Path split failed", STDERR_FILENO), \
		free(path_env), GENERAL_ERROR);
	ret = concat_path(cmd[0], dirs, path);
	if (ret)
		return (clean_array(dirs), ret);
	clean_array(dirs);
	return (0);
}
