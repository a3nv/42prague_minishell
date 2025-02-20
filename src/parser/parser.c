/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 22:31:45 by iasonov           #+#    #+#             */
/*   Updated: 2025/02/20 21:32:05 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	loop_tokens(t_state *state, t_ast_node **root, t_ast_node **cur_node)
{
	t_list			*list_item;
	t_token			*token;

	list_item = state->token_list;
	while (list_item)
	{
		token = (t_token *)list_item->content;
		if (is_redirect(token->type))
		{
			create_redirect_node(cur_node, &list_item, token);
			list_item = list_item->next;
			continue ;
		}
		if (token->type == TOKEN_PIPE)
		{
			create_pipe_node(root, cur_node);
			list_item = list_item->next;
			continue ;
		}
		if (token->type == TOKEN_WORD)
		{
			create_command_node(cur_node, token, state);
		}
		list_item = list_item->next;
	}
}

t_ast_node	*parse_tokens(t_state *state)
{
	t_ast_node		*root;
	t_ast_node		*cur_node;

	cur_node = NULL;
	root = NULL;
	loop_tokens(state, &root, &cur_node);
	if (root && cur_node)
		root->right = cur_node;
	if (root)
		return (root);
	return (cur_node);
}
