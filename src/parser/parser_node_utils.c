/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_node_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:18:32 by iasonov           #+#    #+#             */
/*   Updated: 2025/02/16 14:12:00 by iasonov          ###   ########.fr       */
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
	node->redirection.infile = NULL;
	node->redirection.outfile = NULL;
	node->redirection.heredoc_delim = NULL;
	node->redirection.append = 0;
	return (node);
}

/*
 * init_node_args:
 *   Initializes the 'args' field of the given node by:
 *   - Counting the number of arguments from the provided list.
 *   - Allocating enough space for the argument array (at least one element).
 *   - Duplicating the provided value into the first argument slot.
 *   - Setting the next slot to NULL.
 *   Returns 0 on success or -1 on failure.
 */
static int	init_node_args(t_ast_node *node, char *value, t_list *list)
{
	size_t	arg_count;

	arg_count = count_args(list);
	if (arg_count == 0)
		arg_count = 1;
	node->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!node->args)
		return (-1);
	node->args[0] = ft_strdup(value);
	if (!node->args[0])
	{
		free(node->args);
		return (-1);
	}
	node->args[1] = NULL;
	return (0);
}

/*
 * create_ast_node:
 *   Allocates a new AST node of the given type. If a value is provided,
 *   it initializes the node's argument array using init_node_args.
 */
t_ast_node	*create_ast_node(t_node_type type, char *value, t_list *list)
{
	t_ast_node	*node;

	node = allocate_node(type);
	if (!node)
		return (NULL);
	if (value)
	{
		if (init_node_args(node, value, list) < 0)
		{
			free(node);
			return (NULL);
		}
	}
	return (node);
}
