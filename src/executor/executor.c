/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 00:40:18 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/19 23:03:22 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

void	execute_builtin(t_ast_node *node)
{
	printf("resut: %d", ft_strcmp(node->args[0], "pwd"));
	if (ft_strcmp(node->args[0], "pwd") == 0)
		builtin_pwd();
}

void	execute_node(t_ast_node *node)
{
	if (node->type == NODE_COMMAND)
		execute_builtin(node);
	else if (node->type == NODE_PIPE)
		printf("Executing pipe\n");
	else if (node->type == NODE_REDIRECTION)
		printf("Executing redir \n");
	else
		printf("Unknown command type %d", node->type);
}

void	execute_ast(t_ast_node *node)
{
	if (!node)
		return ;
	execute_ast(node->left);
	execute_ast(node->right);
	execute_node(node);
	return ;
}
