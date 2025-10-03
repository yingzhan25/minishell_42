/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:14:06 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/28 17:02:53 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	change_quote(char c, int *quote)
{
	if (c == '\'')
	{
		if (*quote == q_sopen)
			*quote = q_close;
		else if (*quote == q_close)
			*quote = q_sopen;
		else
			return (0);
	}
	else if (c == '"')
	{
		if (*quote == q_dopen)
			*quote = q_close;
		else if (*quote == q_close)
			*quote = q_dopen;
		else
			return (0);
	}
	return (1);
}
/**
 * Quote status machine:
 * if quote closed, then one of two quotes ocurrs, status opened;
 * if already in quote, then the same quote ocurrs, status closed;
 * if already in quote, then another quote occurs, status unchanged
 */