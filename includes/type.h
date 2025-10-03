/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 11:19:51 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/28 11:39:06 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_H
# define TYPE_H

typedef enum e_node_type		t_node_type;
typedef enum e_redir_type		t_redir_type;
typedef struct s_redir_token	t_redir_token;
typedef struct s_command		t_command;
typedef struct s_pipe			t_pipe;
typedef struct s_node			t_node;
typedef struct s_env			t_env;
typedef struct s_shell			t_shell;

#endif