/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_printer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 23:04:44 by iasonov           #+#    #+#             */
/*   Updated: 2025/02/15 21:24:54 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

void	print_command(t_ast_node *node, int depth)
{
	int	i;
	int	j;

	printf("COMMAND Node:\n");
	i = 0;
	while (node->args && node->args[i])
	{
		j = 0;
		while (j < depth)
		{
			printf("    ");
			j++;
		}
		printf("    ├── Argument: %s\n", node->args[i]);
		i++;
	}
}

void	print_redirect(t_ast_node *node)
{
	if (node->args)
	{
		if (strcmp(node->args[0], ">") == 0)
			printf("REDIRECT OUT Node\n");
		else if (strcmp(node->args[0], ">>") == 0)
			printf("REDIRECT APPEND Node\n");
		else if (strcmp(node->args[0], "<") == 0)
			printf("REDIRECT IN Node\n");
		else if (strcmp(node->args[0], "<<") == 0)
			printf("REDIRECT HEREDOC Node\n");
		else
			printf("UNKNOWN REDIRECTION Node\n");
	}
	else
		printf("REDIRECTION Node with NO Operator\n");
}

void	print_node(t_ast_node *node, int depth)
{
	if (!node)
		return ;
	if (node->type == NODE_COMMAND)
		print_command(node, depth);
	else if (node->type == NODE_PIPE)
		printf("PIPE Node\n");
	else if (node->type == NODE_REDIRECTION)
		print_redirect(node);
	else
		printf("UNKNOWN Node\n");
}

void	pad(int depth)
{
	int	i;

	i = 0;
	while (i < depth)
	{
		printf("    ");
		i++;
	}
}

void	display_ast(t_ast_node *node, int depth)
{
	if (!node)
		return ;
	pad(depth);
	print_node(node, depth);
	if (node->left)
	{
		pad(depth + 1);
		printf("├── Left:\n");
		display_ast(node->left, depth + 2);
	}
	if (node->right)
	{
		pad(depth + 1);
		printf("└── Right:\n");
		display_ast(node->right, depth + 2);
	}
}
