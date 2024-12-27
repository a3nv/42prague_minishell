/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 00:40:18 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/27 22:09:31 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

void	execute_builtin(t_ast_node *node, t_state *state)
{
	if (ft_strcmp(node->args[0], "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(node->args[0], "cd") == 0)
		builtin_cd(node);
	else if (ft_strcmp(node->args[0], "exit") == 0)
		builtin_exit(state);
	else if (ft_strcmp(node->args[0], "echo") == 0)
		builtin_echo(node);
	else if (ft_strcmp(node->args[0], "env") == 0)
		builtin_env(state);
	else if (ft_strcmp(node->args[0], "export") == 0)
		builtin_export(node, state);
	else if (ft_strcmp(node->args[0], "unset") == 0)
		builtin_unset(node, state);
}

void	execute_node(t_ast_node *node, t_state *state)
{
	if (node->type == NODE_COMMAND)
		execute_builtin(node, state);
	else if (node->type == NODE_PIPE)
		printf("Executing pipe\n");
	else if (node->type == NODE_REDIRECTION)
		printf("Executing redir \n");
	else
		printf("Unknown command type %d", node->type);
}

void	execute_ast(t_ast_node *node, t_state *state)
{
	if (!node)
		return ;
	execute_ast(node->left, state);
	execute_ast(node->right, state);
	execute_node(node, state);
	return ;
}
