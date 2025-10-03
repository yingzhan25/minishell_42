/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:56:42 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/29 13:28:51 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_env_list(t_env *envList)
{
	t_env	*tmp;

	while (envList)
	{
		tmp = envList;
		envList = envList->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}

void	clean_shell(t_shell	*shell)
{
	rl_clear_history();
	free_env_list(shell->env_list);
	free(shell);
}
