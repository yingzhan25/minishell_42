/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkubaev <jkubaev@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 09:49:49 by jkubaev           #+#    #+#             */
/*   Updated: 2025/09/29 11:47:18 by jkubaev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * append_before_dollar:
 *  Appends the substring before the next '$' character 
 * from input to the result.
 *
 * Parameters:
 *  - result: the current expanded string
 *  - input: pointer to the input string pointer (will be advanced past '$')
 *
 * Returns:
 *  - Newly allocated string with the appended part
 *  - NULL on allocation failure
 */
static char	*append_before_dollar(char *result, char **input)
{
	char	*new_part;
	char	*temp_result;
	char	*next_dollar;
	int		len;

	next_dollar = ft_strchr((*input), '$');
	len = next_dollar - (*input);
	new_part = ft_substr_g((*input), 0, len);
	if (!new_part)
		return (printf(ALLOCATION_FAIL), NULL);
	temp_result = ft_strjoin_g(result, new_part);
	if (!temp_result)
		return (printf(ALLOCATION_FAIL), free(new_part), NULL);
	(*input) = next_dollar + 1;
	free(result);
	free(new_part);
	return (temp_result);
}

/*
 * extract_var_name:
 *  Extracts the environment variable name starting at input.
 *
 * Parameters:
 *  - input: pointer to the start of the variable name
 *  - var_name_end: output pointer to the character after the variable name
 *
 * Returns:
 *  - Newly allocated variable name string
 *  - NULL on allocation failure
 */
static char	*extract_var_name(char *input, char **var_name_end)
{
	char	*var_name;
	int		len;

	(*var_name_end) = input;
	while (ft_isalnum((**var_name_end)) || (**var_name_end) == '_')
		(*var_name_end)++;
	len = *var_name_end - input;
	var_name = ft_substr_g(input, 0, len);
	if (!var_name)
		return (printf(ALLOCATION_FAIL), NULL);
	return (var_name);
}

/*
 * append_var_value:
 *  Appends the value of the given environment variable to result.
 *
 * Parameters:
 *  - var_name: pointer to the name of the environment variable
 *  - result: pointer to the current result string (will be updated)
 *  - shell: shell structure to retrieve environment variable
 *
 * Returns:
 *  - 0 on success
 *  - 1 on allocation failure
 *
 * Notes:
 *  - Frees var_name and updates result in-place
 */
static int	append_var_value(char **var_name, char **result, t_shell *shell)
{
	char	*temp_result;
	char	*var_value;

	var_value = get_env_value(shell, *var_name);
	if (var_value)
	{
		temp_result = ft_strjoin_g(*result, var_value);
		if (!temp_result)
			return (printf(ALLOCATION_FAIL), free(*var_name), free(*result), 1);
		free(*result);
		*result = temp_result;
	}
	free(*var_name);
	return (0);
}

/*
 * append_result_leftover:
 *  Appends any remaining input string to the result after variable expansions.
 *
 * Parameters:
 *  - result: pointer to the current result string
 *  - input: pointer to the remaining input string
 *
 * Returns:
 *  - 0 on success
 *  - 1 on allocation failure
 */
static int	append_result_leftover(char	**result, char **input)
{
	char	*temp_result;

	temp_result = ft_strjoin_g(*result, *input);
	if (!temp_result)
		return (printf(ALLOCATION_FAIL), 1);
	free(*result);
	*result = temp_result;
	return (0);
}

/*
 * exp_heredoc:
 *  Expands environment variables in the given input string for heredoc.
 *
 * Parameters:
 *  - input: the raw heredoc input string containing potential $VAR
 *  - shell: the shell structure to retrieve environment variables
 *
 * Returns:
 *  - Newly allocated expanded string
 *  - NULL on failure
 *
 * Behavior:
 *  - Iterates over the input string, finding '$' characters.
 *  - Extracts variable names and appends their values from the environment.
 *  - Appends literal text between variables to the result.
 *  - Ensures proper memory management and returns NULL on allocation failure.
 */
char	*exp_heredoc(char *input, t_shell *shell)
{
	char	*result;
	char	*var_name;
	char	*var_name_end;

	result = ft_strdup("");
	if (!result)
		return (printf(ALLOCATION_FAIL), NULL);
	while (ft_strchr(input, '$'))
	{
		result = append_before_dollar(result, &input);
		if (!result)
			return (NULL);
		var_name = extract_var_name(input, &var_name_end);
		if (!var_name)
			return (printf(ALLOCATION_FAIL), NULL);
		if (append_var_value(&var_name, &result, shell))
			return (NULL);
		input = var_name_end;
	}
	if (append_result_leftover(&result, &input))
		return (NULL);
	return (result);
}
