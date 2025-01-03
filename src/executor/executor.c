/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 00:40:18 by iasonov           #+#    #+#             */
/*   Updated: 2025/01/03 18:36:13 by iasonov          ###   ########.fr       */
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
	else if (ft_strcmp(node->args[0], "grep") == 0)
		builtin_grep(node);
	else if (ft_strcmp(node->args[0], "wc") == 0)
		builtin_wc();
}

void	execute_ast(t_ast_node *node, t_state *state)
{
	if (!node)
		return ;
	if (node->type == NODE_COMMAND)
	{
		if (is_builtin(node))
			execute_builtin(node, state);
		else
			execute_binary(node, state);
	}
	else if (node->type == NODE_PIPE)
		execute_pipe(node, state);
	else if (node->type == NODE_REDIRECTION)
		printf("Executing redir \n");
	else
		printf("Unknown command type %d", node->type);
}
