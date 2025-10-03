/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 11:17:35 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/29 17:22:23 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	* setup_in_redir function sets up input redirection for a command.
	*
	* @param redir: Pointer to a t_redir_token structure representing 
	* the input redirection.
	*
	* Behavior:
	* - Opens the file specified in redir->file in read-only mode.
	* - If the file cannot be opened, prints an error and returns GENERAL_ERROR.
	* - Uses dup2 to redirect STDIN to the opened file descriptor.
	* - Closes the original file descriptor after duplication.
	*
	* @return
	*   int → 0 on success, GENERAL_ERROR on failure.
 */
static int	setup_in_redir(t_redir_token *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
		return (perror(redir->file), GENERAL_ERROR);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (close(fd), perror("dup2"), GENERAL_ERROR);
	close(fd);
	return (0);
}

/*
	* setup_out_redir function sets up input redirection for a command.
	*
	* @param redir: Pointer to a t_redir_token structure representing 
	* the input redirection.
	*
	* Behavior:
	* - Opens the file specified in redir->file in read-only mode.
	* - If the file cannot be opened, prints an error and returns GENERAL_ERROR.
	* - Uses dup2 to redirect STDOUT to the opened file descriptor.
	* - Closes the original file descriptor after duplication.
	*
	* @return
	*   int → 0 on success, GENERAL_ERROR on failure.
 */
static int	setup_out_redir(t_redir_token *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror(redir->file), GENERAL_ERROR);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (close(fd), perror("dup2"), GENERAL_ERROR);
	close(fd);
	return (0);
}

/*
 * setup_append_redir function sets up output 		
 * redirection in append mode for a command.
 *
 * @param redir: Pointer to a t_redir_token structure 
 * 	representing the append redirection.
 *
 * Behavior:
 * - Opens the file specified in redir->file in write-only mode, 
 * creates it if it doesn't exist, 
 *   and sets the file pointer to the end of the 
 * 	file (append mode) with permissions 0644.
 * - If the file cannot be opened, prints an error and returns GENERAL_ERROR.
 * - Uses dup2 to redirect STDOUT to the opened file descriptor.
 * - Closes the original file descriptor after duplication.
 *
 * @return
 *   int → 0 on success, GENERAL_ERROR on failure.
 */

static int	setup_append_redir(t_redir_token *redir)
{
	int	fd;

	fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (perror(redir->file), GENERAL_ERROR);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (close(fd), perror("dup2"), GENERAL_ERROR);
	close(fd);
	return (0);
}

/*
	* setup_heredoc_redir function sets up input redirection 
	* from a heredoc for a command.
	*
	* @param heredoc_fd: File descriptor of the heredoc temporary file or pipe.
	* @param redir: Pointer to a t_redir_token structure 
	* representing the heredoc redirection.
	*
	* Behavior:
	* - Checks if the heredoc file descriptor is valid.  
	* If not, prints an error and returns GENERAL_ERROR.
	* - Uses dup2 to redirect STDIN to the heredoc file descriptor.
	* - Closes the original file descriptor after duplication.
	*
	* @return
	*   int → 0 on success, GENERAL_ERROR on failure.
 */
static int	setup_heredoc_redir(int heredoc_fd, t_redir_token *redir)
{
	int	fd;

	fd = heredoc_fd;
	if (fd == -1)
		return (perror(redir->file), GENERAL_ERROR);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (close(fd), perror("dup2"), GENERAL_ERROR);
	close(fd);
	return (0);
}

/*
	* setup_redirections function sets up all input/output redirections 
	* for a command node.
	*
	* @param nodes: Pointer to the command node containing 
	* a linked list of redirection tokens.
	*
	* Behavior:
	* - Iterates through all redirection tokens in nodes->cmd.redir_token.
	* - Depending on the redirection type, calls 
	* the corresponding setup function:
	*     - IN      → setup_in_redir
	*     - OUT     → setup_out_redir
	*     - APPEND  → setup_append_redir
	*     - HEREDOC → setup_heredoc_redir
	* - Stops and returns an error code immediately 
	* if any redirection setup fails.
	*
	* @return
	*   int → 0 on success, GENERAL_ERROR (or the code from the 
	* setup functions) on failure.
 */
int	setup_redirections(t_node *nodes)
{
	t_redir_token	*tmp;
	int				ret;
	int				heredoc;

	heredoc = 1;
	tmp = nodes->cmd.redir_token;
	while (tmp)
	{
		if (tmp->redir_type == IN)
			ret = setup_in_redir(tmp);
		else if (tmp->redir_type == OUT)
			ret = setup_out_redir(tmp);
		else if (tmp->redir_type == APPEND)
			ret = setup_append_redir(tmp);
		else if (tmp->redir_type == HEREDOC && heredoc)
		{
			heredoc = 0;
			ret = setup_heredoc_redir(nodes->cmd.heredoc_fd, tmp);
		}
		if (ret != 0)
			return (ret);
		tmp = tmp->next;
	}
	return (0);
}
