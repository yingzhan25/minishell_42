/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:03:16 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/30 17:43:12 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define GENERAL_ERROR 1
# define SYNTAX_ERROR 2
# define COMMAND_NOT_EXECUTABLE 126
# define COMMAND_NOT_FOUND 127

# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"
# include "type.h"
# include "tokenizing.h"
# include "execution.h"
# include "parsing.h"

extern sig_atomic_t				g_sig_received;

/**
 * COMMAND : command (ls, grep, etc.)
 * PIPE : pipe (|)
 * REDIR : redirection(<, >, <<, >>)
 */
typedef enum e_node_type
{
	COMMAND,
	PIPE,
	REDIR,
}	t_node_type;

/**
 * IN : <
 * OUT : >
 * APPEND : >>
 * HEREDOC : <<
 */
typedef enum e_redir_type
{
	IN,
	OUT,
	APPEND,
	HEREDOC,
}	t_redir_type;

/**
 * redir_type : IN, OUT..
 * file : Filename or limiter
 * next : token for redirection
 */
typedef struct s_redir_token
{
	t_redir_type			redir_type;
	char					*file;
	struct s_redir_token	*next;
}	t_redir_token;

/**
 * cmd : ["-l"], ["txt"], etc.
 * redir_token;
 * heredoc_fd : Redirection node if exists
 */
typedef struct s_command
{
	char			**cmd;
	t_redir_token	*redir_token;
	int				heredoc_fd;
}	t_command;

/**
 * left : left child (Command or Pipe)
 * right : right child (Command or Pipe)
 */
typedef struct s_pipe
{
	struct s_node	*left;
	struct s_node	*right;
}	t_pipe;

/**
 * type : COMMAND, PIPE, REDIR
 * cmd : Command Node uchun
 * pipe : Pipe Node uchun
 */
typedef struct s_node
{
	t_node_type	type;
	union
	{
		struct s_command	cmd;
		struct s_pipe		pipe;
	};
}	t_node;

typedef struct s_env
{
	char			*name;
	char			*value;
	int				equal_sign;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	t_env	*env_list;
	t_node	*nodes;
	char	*input;
	int		exit_code;
}	t_shell;

void	setup_signals(void (*signal_handler)(int));
void	signal_handler_main(int sig);
void	signal_handler_exit(int sig);
void	signal_handler_wait(int sig);
void	find_heredoc(t_node *node, t_shell *shell);
int		expand_write(char *input, t_shell *shell, int pipe_w);
void	print_warning(char *s);
void	free_env_list(t_env *envList);
void	clean_shell(t_shell	*shell);
t_shell	*init_envp(char **envp);
char	**envp_to_array(t_env *env_list);
char	*exp_heredoc(char *input, t_shell *shell);

#endif