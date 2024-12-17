/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 00:40:18 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/17 00:54:45 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

void	execute_node(t_ast_node *node)
{
	int	i;

	if (node->type == NODE_COMMAND)
	{
		printf("Executing command: ");
		i = 0;
		while(node->args && node->args[i])
		{
			printf("%s ", node->args[i]);
			i++;
		}
		printf("\n");
	}
	else if (node->type == NODE_PIPE)
	{
		printf("Executing pipe\n");
	}
	else if (node->type == NODE_REDIRECTION)
	{
		printf("Executing redir \n");
	}
	else
	{
		printf("Unknown command type %d", node->type);
	}
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
