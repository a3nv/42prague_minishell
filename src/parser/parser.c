/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 22:31:45 by iasonov           #+#    #+#             */
/*   Updated: 2025/01/21 21:21:24 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_pipe_node(t_ast_node **root, t_ast_node **current_node,
		t_list *list)
{
	t_ast_node	*pipe_node;

	if (!*current_node)
		return ;
	pipe_node = create_ast_node(NODE_PIPE, "|", list);
	if (!pipe_node)
		return ;
	if (!*root)
		pipe_node->left = *current_node;
	else
	{
		pipe_node->left = *root;
		(*root)->right = *current_node;
	}
	*root = pipe_node;
	*current_node = NULL;
}

void	create_redirect_node(t_ast_node **current_node, t_list **list_item,
		t_token *token, t_state *state)
{
	t_ast_node	*redirect_node;

	redirect_node = create_ast_node(NODE_REDIRECTION, token->value, *list_item);
	if (!redirect_node)
		return ;
	if (*current_node)
		redirect_node->left = *current_node;
	*current_node = redirect_node;
	*list_item = (*list_item)->next;
	if (*list_item && (*list_item)->content)
	{
		create_command_node(&redirect_node->right, *list_item,
			((t_token *)(*list_item)->content), state);
	}
}

void	create_command_node(t_ast_node **cur, t_list *list_item,
		t_token *token, t_state *state)
{
	int		arg_count;
	char	*expanded_value;

	if (token->expandable && ft_strchr(token->value, '$'))
	{
		expanded_value = expand_variable(state, token->value);
		if (!expanded_value)
			expanded_value = ft_strdup("");
	}
	else
		expanded_value = ft_strdup(token->value);
	if (*cur)
	{
		arg_count = 0;
		while ((*cur)->args[arg_count])
			arg_count++;
		(*cur)->args[arg_count] = expanded_value;
		(*cur)->args[arg_count + 1] = NULL;
		(*cur)->argc = arg_count + 1;
	}
	else
	{
		*cur = create_ast_node(NODE_COMMAND, expanded_value, list_item);
		free(expanded_value);
	}
}

t_ast_node	*parse_tokens(t_state *state)
{
	t_list			*list_item;
	t_token			*token;
	t_ast_node		*root;
	t_ast_node		*current_node;

	list_item = state->token_list;
	current_node = NULL;
	root = NULL;
	while (list_item)
	{
		token = (t_token *)list_item->content;
		if (token->type == TOKEN_WORD)
			create_command_node(&current_node, list_item, token, state);
		if (token->type == TOKEN_PIPE)
			create_pipe_node(&root, &current_node, list_item);
		else if (is_redirect(token->type))
			create_redirect_node(&current_node, &list_item, token, state);
		list_item = list_item->next;
	}
	if (root && current_node)
		root->right = current_node;
	if (root)
		return (root);
	return (current_node);
}
