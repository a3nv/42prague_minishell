/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_node_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:18:32 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/18 15:28:02 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast_node	*create_node(t_token_type type)
{
	t_ast_node	*node;

	(void)type;
	node = malloc(sizeof(t_ast_node));
	if (!node)
	{
		ft_putstr_fd("Error: malloc failed in create_node\n", 2);
		return (NULL);
	}
	node->args = NULL;
	node->right = NULL;
	node->left = NULL;
	return (node);
}

t_ast_node	*create_file_node(t_token *temp_token)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->args = malloc(sizeof(char *) * 2);
	if (!node->args)
	{
		free(node);
		return (NULL);
	}
	node->args[0] = temp_token->value;
	node->args[1] = NULL;
	node->left = NULL;
	node->right = NULL;
	free(temp_token);
	return (node);
}

t_ast_node	*allocate_node(t_node_type type)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	node->args = NULL;
	return (node);
}

t_ast_node	*create_ast_node(t_node_type type, char *value, t_list *list)
{
	t_ast_node	*node;

	node = allocate_node(type);
	if (!node)
		return (NULL);
	if (value)
	{
		node->args = malloc(sizeof(char *) * (count_args(list) + 1));
		if (!node->args)
		{
			free(node);
			return (NULL);
		}
		node->args[0] = ft_strdup(value);
		if (!node->args[0])
		{
			free(node->args);
			free(node);
			return (NULL);
		}
		node->args[1] = NULL;
	}
	return (node);
}
