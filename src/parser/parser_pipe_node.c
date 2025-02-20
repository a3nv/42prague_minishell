/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 21:00:09 by iasonov           #+#    #+#             */
/*   Updated: 2025/02/20 21:19:37 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_pipe_node(t_ast_node **root, t_ast_node **current_node)
{
	t_ast_node	*pipe_node;

	if (!*current_node)
		return ;
	pipe_node = create_ast_node(NODE_PIPE, "|");
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
