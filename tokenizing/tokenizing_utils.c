/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:53:25 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/28 17:23:09 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*Add new nodes to the back of link list*/
void	add_tokens(t_token **list, t_token_type type, char *value)
{
	t_token	*new;
	t_token	*last;

	new = malloc(sizeof(t_token));
	if (!new)
	{
		free(value);
		clean_tokens(list, 1);
	}
	new->type = type;
	new->value = value;
	new->next = NULL;
	if (!*list)
	{
		*list = new;
		return ;
	}
	last = *list;
	while (last->next)
		last = last->next;
	last->next = new;
}

/*Attach to buffer char by char*/
void	ft_realloc(int pos, char c, char **value, t_token **list)
{
	char	*tmp;
	int		i;

	tmp = malloc(pos + 2);
	if (!tmp)
	{
		if (!*value)
			free(*value);
		*value = NULL;
		clean_tokens(list, 1);
	}
	i = 0;
	if (*value)
	{
		while (i < pos)
		{
			tmp[i] = (*value)[i];
			i++;
		}
		free(*value);
	}
	tmp[pos] = c;
	tmp[pos + 1] = 0;
	*value = tmp;
}

int	break_condition(int quote, char c)
{
	if (!quote)
	{
		if ((!c || c == ' ' || (c >= '\t' && c <= '\r')) || ft_strchr("|><", c))
			return (1);
	}
	return (0);
}

int	get_in_quote(int quote, char c)
{
	if (quote == q_dopen && c == '"' )
		return (0);
	else if (quote == q_sopen && c == '\'')
		return (0);
	return (1);
}

int	is_variable(int quote, char *s)
{
	if (quote == q_dopen && s[0] == '$' && (s[1] == '_' \
		|| s[1] == '?' || ft_isalpha(s[1])))
		return (1);
	else if (quote == q_close && s[0] == '$' \
		&& (s[1] == '_' || s[1] == '?' || ft_isalpha(s[1])))
		return (1);
	else
		return (0);
}
