/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 22:19:04 by javokhir          #+#    #+#             */
/*   Updated: 2025/09/30 15:43:18 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * If quote unclosed, return syntax error;
 * skip spaces;
 * logical tokens -> specify_tokens();
 * neither space nor sprecial token without quotation -> handle_word();
 */

static int	is_word(char c, int quote)
{
	if (c && !(ft_strchr("|><", c) && !quote))
	{
		if (!((c == ' ' || (c >= '\t' && c <= '\r')) && !quote))
			return (1);
	}
	return (0);
}

t_token	*ft_tokenize(char *s, t_shell *shell)
{
	t_token	*list;
	int		i;
	int		quote;

	list = NULL;
	quote = q_close;
	i = 0;
	while (s[i])
	{
		while (s[i] == ' ' || (s[i] >= '\t' && s[i] <= '\r'))
			i++;
		if (s[i] == '\'' || s[i] == '"')
			i += change_quote(s[i], &quote);
		if (s[i] && !quote && ft_strchr("|><", s[i]))
			i += specify_tokens(s + i, &list);
		if (is_word(s[i], quote))
			i += handle_words(s + i, &quote, &list, shell);
	}
	if (quote)
	{
		shell->exit_code = SYNTAX_ERROR;
		return (clean_tokens(&list, 0), ft_putstr_fd(ERROR, 2), NULL);
	}
	return (add_tokens(&list, T_EOF, NULL), list);
}
