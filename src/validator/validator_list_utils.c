/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_list_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:12:23 by iasonov           #+#    #+#             */
/*   Updated: 2025/02/15 20:12:37 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redirection(t_token *token)
{
	return (token->type == TOKEN_OUTPUT || token->type == TOKEN_APPEND
		|| token->type == TOKEN_INPUT || token->type == TOKEN_HEREDOC);
}

int	is_pipe(t_token *token)
{
	return (token->type == TOKEN_PIPE);
}
