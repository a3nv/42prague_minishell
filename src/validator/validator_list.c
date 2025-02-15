/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 02:01:13 by iasonov           #+#    #+#             */
/*   Updated: 2025/02/15 20:15:30 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_invalid_start(t_list *tokens)
{
	t_token	*current;

	current = (t_token *)tokens->content;
	if (is_redirection(current) || is_pipe(current))
	{
		ft_write("minishell: syntax error near unexpected token `",
			STDOUT_FILENO);
		ft_write(current->value, STDOUT_FILENO);
		ft_write("'\n", STDOUT_FILENO);
		return (1);
	}
	return (0);
}

int	check_missing_redirection_target(t_token *current, t_list *next_item)
{
	if (is_redirection(current) && !next_item)
	{
		ft_write("minishell: syntax error near unexpected token `newline'\n",
			2);
		return (1);
	}
	return (0);
}

int	check_invalid_pipe_usage(t_token *current, t_list *next_item)
{
	t_token	*next_token;

	if (is_pipe(current))
	{
		if (!next_item)
		{
			ft_write("minishell: syntax error near unexpected token `|'\n",
				STDOUT_FILENO);
			return (1);
		}
		next_token = (t_token *)next_item->content;
		if (is_pipe(next_token))
		{
			ft_write("minishell: syntax error near unexpected token `|'\n",
				STDOUT_FILENO);
			return (1);
		}
	}
	return (0);
}

int	validate_tokens(t_list *tokens)
{
	t_token	*current;
	t_list	*next_item;
	int		has_command;

	if (!tokens || check_invalid_start(tokens))
		return (1);
	has_command = 0;
	while (tokens)
	{
		current = (t_token *)tokens->content;
		next_item = tokens->next;
		if (current->type == TOKEN_WORD)
			has_command = 1;
		if (!has_command && (is_redirection(current) || is_pipe(current)))
			return (check_invalid_start(tokens));
		if (check_missing_redirection_target(current, next_item))
			return (1);
		if (check_invalid_pipe_usage(current, next_item))
			return (1);
		tokens = tokens->next;
	}
	return (0);
}
