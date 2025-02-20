/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect_node.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:58:08 by iasonov           #+#    #+#             */
/*   Updated: 2025/02/20 21:08:06 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_redirect_value(t_ast_node *redirect_node, t_token *token,
		char *value)
{
	if (token->type == TOKEN_INPUT)
		redirect_node->redirection.infile = ft_strdup(value);
	else if (token->type == TOKEN_OUTPUT)
	{
		redirect_node->redirection.outfile = ft_strdup(value);
		redirect_node->redirection.append = 0;
	}
	else if (token->type == TOKEN_APPEND)
	{
		redirect_node->redirection.outfile = ft_strdup(value);
		redirect_node->redirection.append = 1;
	}
	else if (token->type == TOKEN_HEREDOC)
		redirect_node->redirection.heredoc_delim = ft_strdup(value);
}

void	create_redirect_node(t_ast_node **current_node, t_list **list_item,
		t_token *token)
{
	t_ast_node	*redirect_node;
	t_token		*next_token;

	if (!list_item || !(*list_item) || !(*list_item)->next)
		return ;
	next_token = (t_token *)(*list_item)->next->content;
	if (next_token->type != TOKEN_WORD)
		return ;
	redirect_node = create_ast_node(NODE_REDIRECTION, token->value);
	if (!redirect_node)
		return ;
	if (*current_node)
		redirect_node->left = *current_node;
	*current_node = redirect_node;
	set_redirect_value(redirect_node, token, next_token->value);
	*list_item = (*list_item)->next;
}
