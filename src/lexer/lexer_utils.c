/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:05:25 by aevstign          #+#    #+#             */
/*   Updated: 2025/02/15 19:57:44 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*strip_quotes(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len >= 2 && ((str[0] == '\'' && str[len - 1] == '\'')
			|| (str[0] == '\"' && str[len - 1] == '\"')))
		return (ft_strndup(str + 1, len - 2));
	return (ft_strdup(str));
}

t_token	*create_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = TOKEN_NULL;
	token->value = NULL;
	return (token);
}

void	free_token(t_token *token)
{
	if (!token)
		return ;
	free(token->value);
	free(token);
}

t_token_type	get_char_type(char c)
{
	if (c == '|')
		return (TOKEN_PIPE);
	if (c == '\'')
		return (TOKEN_SINGLE_QUOTE);
	if (c == '"')
		return (TOKEN_DOUBLE_QUOTE);
	if (c == '>')
		return (TOKEN_OUTPUT);
	if (c == '<')
		return (TOKEN_INPUT);
	if (c == '=')
		return (TOKEN_EQUALS);
	return (TOKEN_WORD);
}

t_token_type	get_operator_type(char *str, int *advance)
{
	if (!str || !str[0])
		return (TOKEN_ERROR);
	if (str[0] == '>' && str[1] == '>')
	{
		*advance = 2;
		return (TOKEN_APPEND);
	}
	else if (str[0] == '<' && str[1] == '<')
	{
		*advance = 2;
		return (TOKEN_HEREDOC);
	}
	if (str[0] == '>')
	{
		*advance = 1;
		return (TOKEN_OUTPUT);
	}
	else if (str[0] == '<')
	{
		*advance = 1;
		return (TOKEN_INPUT);
	}
	*advance = 1;
	return (get_char_type(str[0]));
}
