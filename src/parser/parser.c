/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 22:31:45 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/09 00:02:12 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast_node	*create_ast_node(t_node_type type, char *value, t_list *list)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	if (value)
	{
		node->args = malloc(sizeof(char *) * count_args(list));
		if (!node->args)
			return  (NULL);
		node->args[0] = ft_strdup(value);
		if (!node->args[0])
		{
			free(node);
			return (NULL);
		}
	}
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	create_pipe_node(t_ast_node **root, t_ast_node **current_node, t_list *list)
{
	t_ast_node	*pipe_node;

	pipe_node = create_ast_node(NODE_PIPE, "|", list);
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

	redirect_node = create_ast_node(NODE_REDIRECTION, token->value, *list_item);
	if (!redirect_node)
		return ;
	*list_item = (*list_item)->next;
	if (*list_item && (*list_item)->content)
	{
		file_token = (t_token *)(*list_item)->content;
		redirect_node->right = create_ast_node(NODE_COMMAND, file_token->value, *list_item);
		if (!redirect_node->right)
		{
			free(redirect_node->args);
			free(redirect_node);
			return ;
		}
	}
	else
	{
		free(redirect_node->args); // todo: manually clear eachentry in args
		free(redirect_node);
		return ;
	}
	if (*current_node)
		(*current_node)->right = redirect_node;
	else
		(*current_node) = redirect_node;
}

void	create_command_node(t_ast_node **current_node, t_list *list_item, t_token *token)
{
	int		arg_count;

	if (!*current_node)
		*current_node = create_ast_node(NODE_COMMAND, token->value, list_item);
	else
	{
		arg_count = 0;
		while ((*current_node)->args[arg_count])
			arg_count++;
		(*current_node)->args[arg_count] = ft_strdup(token->value);
		(*current_node)->args[arg_count + 1] = NULL;
	}

}

t_ast_node	*parse_tokens(t_list *token_list)
{
	t_list			*list_item;
	t_token			*token;
	t_ast_node		*root;
	t_ast_node		*current_node;

	list_item = token_list;
	current_node = NULL;
	root = NULL;
	while (list_item)
	{
		token = (t_token *)list_item->content;
		if (token->type == TOKEN_PIPE)
			create_pipe_node(&root, &current_node, list_item);
		else if (is_redirect(token->type))
			create_redirect_node(&current_node, &list_item, token);
		else
			create_command_node(&current_node, list_item, token);
		list_item = list_item->next;
	}
	if (root)
		return (root);
	else
		return (current_node);
}
