/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 23:28:38 by iasonov           #+#    #+#             */
/*   Updated: 2025/02/16 14:09:54 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_expanded_value(t_state *state, char *key)
{
	char	*value;
	char	*dup;

	if (ft_strcmp(key, "?") == 0)
		return (ft_itoa(state->last_exit_code));
	value = array_list_get_env_value(state->envp_list, key);
	if (value == NULL)
		return (ft_strdup(""));
	dup = ft_strdup(value);
	free(value);
	return (dup);
}

int	handle_exit_code_expansion(char **start, t_state *state, char **result)
{
	char	*expanded_value;
	char	*new_result;

	if (*(*start + 1) != '?')
		return (0);
	expanded_value = ft_itoa(state->last_exit_code);
	if (expanded_value == NULL)
		return (0);
	new_result = ft_strjoin(*result, expanded_value);
	free(*result);
	free(expanded_value);
	if (new_result == NULL)
		return (0);
	*result = new_result;
	*start += 2;
	return (1);
}

char	*handle_variable_expansion(t_state *state, char **start, char *result)
{
	char	*end;
	char	*key;
	char	*expanded_value;
	char	*new_result;

	if (handle_exit_code_expansion(start, state, &result))
		return (result);
	end = *start + 1;
	while (*end && (ft_isalnum(*end) || *end == '_'))
		end++;
	key = ft_substr(*start + 1, 0, end - *start - 1);
	if (key == NULL)
		return (NULL);
	expanded_value = get_expanded_value(state, key);
	free(key);
	if (expanded_value == NULL)
		return (NULL);
	new_result = ft_strjoin(result, expanded_value);
	free(result);
	free(expanded_value);
	*start = end;
	return (new_result);
}

char	*handle_plain_text(char **start, char *result)
{
	char	*end;
	char	*plain_text;
	char	*new_result;

	end = *start;
	while (*end && *end != '$')
		end++;
	plain_text = ft_substr(*start, 0, end - *start);
	if (plain_text == NULL)
		return (NULL);
	new_result = ft_strjoin(result, plain_text);
	free(result);
	free(plain_text);
	*start = end;
	return (new_result);
}

char	*expand_variable(t_state *state, char *value)
{
	char	*result;
	char	*start;

	result = ft_strdup("");
	start = value;
	if (result == NULL)
		return (NULL);
	while (*start)
	{
		if (*start == '$')
			result = handle_variable_expansion(state, &start, result);
		else
			result = handle_plain_text(&start, result);
		if (result == NULL)
			return (NULL);
	}
	return (result);
}
