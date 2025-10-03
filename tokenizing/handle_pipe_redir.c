/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:48:01 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/28 17:19:37 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	specify_tokens_single(char **value, char c, t_token **list)
{
	if (c == '|')
	{
		*value = ft_strdup("|");
		if (!*value)
			clean_tokens(list, 1);
		add_tokens(list, T_PIPE, *value);
	}
	else if (c == '<')
	{
		*value = ft_strdup("<");
		if (!*value)
			clean_tokens(list, 1);
		add_tokens(list, T_LESS, *value);
	}
	else if (c == '>')
	{
		*value = ft_strdup(">");
		if (!*value)
			clean_tokens(list, 1);
		add_tokens(list, T_GREAT, *value);
	}
}

static int	specify_tokens_double(char **value, char c, t_token **list)
{
	if (c == '<')
	{
		*value = ft_strdup("<<");
		if (!*value)
			clean_tokens(list, 1);
		add_tokens(list, T_DLESS, *value);
	}
	else if (c == '>')
	{
		*value = ft_strdup(">>");
		if (!*value)
			clean_tokens(list, 1);
		add_tokens(list, T_DGREAT, *value);
	}
	else if (c == '|')
	{
		specify_tokens_single(value, c, list);
		return (1);
	}
	return (2);
}

/*Specify special tokens and add to the list*/
int	specify_tokens(char *s, t_token **list)
{
	char	*value;

	value = NULL;
	if (*(s + 1) && *(s + 1) == *s)
		return (specify_tokens_double(&value, *s, list));
	else
	{
		specify_tokens_single(&value, *s, list);
		return (1);
	}
}
