/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 22:31:45 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/07 19:19:50 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast_node	*create_ast_node(t_node_type type, char *value)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	if (value)
	{
		node->value = ft_strdup(value);
		if (!node->value)
		{
			free(node);
			return (NULL);
		}
	}
	else
		node->value = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	create_pipe_node(t_ast_node **root, t_ast_node **current_node)
{
	t_ast_node	*pipe_node;

	pipe_node = create_ast_node(NODE_PIPE, "|");
	if (!pipe_node)
		return ;
	pipe_node->left = *current_node;
	*root = pipe_node;
	*current_node = NULL;
}

void	create_redirect_node(t_ast_node **current_node, t_list **list_item,
		t_token *token)
{
	t_ast_node	*redirect_node;
	t_token		*file_token;

	redirect_node = create_ast_node(NODE_REDIRECTION, token->value);
	if (!redirect_node)
		return ;
	*list_item = (*list_item)->next;
	if (*list_item && (*list_item)->content)
	{
		file_token = (t_token *)(*list_item)->content;
		redirect_node->right = create_ast_node(NODE_COMMAND, file_token->value);
		if (!redirect_node->right)
		{
			free(redirect_node->value);
			free(redirect_node);
			return ;
		}
	}
	else
	{
		free(redirect_node->value);
		free(redirect_node);
		return ;
	}
	if (*current_node)
		(*current_node)->right = redirect_node;
	else
		(*current_node) = redirect_node;
}

t_ast_node	*parse_tokens(t_list *token_list)
{
	t_list		*list_item;
	t_token		*token;
	t_ast_node	*root;
	t_ast_node	*current_node;
	char		*new_val;

	list_item = token_list;
	current_node = NULL;
	root = NULL;
	while (list_item)
	{
		token = (t_token *)list_item->content;
		if (token->type == TOKEN_PIPE)
			create_pipe_node(&root, &current_node);
		else if (is_redirect(token->type))
			create_redirect_node(&current_node, &list_item, token);
		else if (token->type == TOKEN_WORD)
		{
			if (!current_node)
				current_node = create_ast_node(NODE_COMMAND, token->value);
			else
			{
				new_val = malloc(ft_strlen(current_node->value)
						+ ft_strlen(token->value) + 2);
				if (new_val)
				{
					strcpy(new_val, current_node->value);
					strcat(new_val, " ");
					strcat(new_val, token->value);
					free(current_node->value);
					current_node->value = new_val;
				}
				else
				{
					free(current_node->value);
				}
				current_node->value = new_val;
			}
		}
		list_item = list_item->next;
	}
	if (root)
		return (root);
	else
		return (current_node);
}
