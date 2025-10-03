/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yingzhan <yingzhan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:51:42 by yingzhan          #+#    #+#             */
/*   Updated: 2025/09/28 17:27:10 by yingzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*Get var_value according to var_name*/
char	*get_env_value(t_shell *shell, char *s)
{
	int		len1;
	int		len2;
	t_env	*tmp;

	if (!shell || !shell->env_list || !s)
		return (NULL);
	tmp = shell->env_list;
	len1 = ft_strlen(s);
	while (tmp)
	{
		len2 = ft_strlen_g(tmp->name);
		if (!len2)
			return (NULL);
		if (!ft_strncmp(s, tmp->name, len1) && len1 == len2)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

/*Treat $EMPTY as $INVALID*/
static char	*expand_var(char *s, t_shell *shell, t_token **list)
{
	char	*var;
	char	*value;

	var = NULL;
	if (!ft_strncmp(s, "?", 1))
		value = ft_itoa(shell->exit_code);
	else
	{
		var = get_env_value(shell, s);
		if (!var || !ft_strcmp(s, "EMPTY"))
			value = ft_strdup("");
		else
			value = ft_strdup(var);
	}
	if (!value)
		clean_tokens(list, 1);
	return (value);
}

/**Interpret $ and expand
 * Only [a-zA-Z_][a-zA-Z0-9_] is treated as valid t_var without $ sign
 * Otherwise taken as t_word*/
char	*handle_dollar(char **s, t_shell *shell, t_token **list)
{
	char	*value;
	int		i;
	char	*var;

	i = 1;
	value = NULL;
	if ((*s)[i] == '?')
	{
		value = expand_var("?", shell, list);
		(*s) += 2;
	}
	else if ((*s)[i] == '_' || ft_isalpha((*s)[i]))
	{
		while ((*s)[i + 1] == '_' || ft_isalnum((*s)[i + 1]))
			i++;
		var = ft_substr((*s), 1, i);
		if (!var)
			clean_tokens(list, 1);
		value = expand_var(var, shell, list);
		free (var);
		(*s) += i + 1;
	}
	return (value);
}
