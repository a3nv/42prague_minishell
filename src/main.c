/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 23:28:11 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/17 00:56:52 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// todo: delete
void	print_node(t_ast_node *node, int depth)
{
	int	i;
	int	j;

	if (!node)
		return;
	if (node->type == NODE_COMMAND)
	{
		printf("COMMAND Node:\n");
		for (i = 0; node->args && node->args[i]; i++) {
			for (j = 0; j < depth; j++)
				printf("    ");
			printf("    ├── Argument: %s\n", node->args[i]);
		}
	}
	else if (node->type == NODE_PIPE)
	{
		printf("PIPE Node\n");
	}
	else if (node->type == NODE_REDIRECTION)
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
	else
		printf("UNKNOWN Node\n");
}

// todo: delete
void	display_ast(t_ast_node *node, int depth)
{
	int	i;

	if (!node)
		return;
	for (i = 0; i < depth; i++)
		printf("    ");
	print_node(node, depth);
	if (node->left)
	{
		for (i = 0; i < depth + 1; i++)
			printf("    ");
		printf("├── Left:\n");
		display_ast(node->left, depth + 2);
	}
	if (node->right)
	{
		for (i = 0; i < depth + 1; i++)
			printf("    ");
		printf("└── Right:\n");
		display_ast(node->right, depth + 2);
	}
}

// int	main(int argc, char *argv[], char **env)
int	main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	char		*input;
	t_list		*list;
	t_ast_node	*ast_node;
	// while(env)
	// {
	// 	printf("%s",*env); 
	// 	env++;
	// }
	// shows what env variable holds
	while (1)
	{
		write(STDOUT_FILENO, "minishell$> ", 11);
		input = get_next_line(STDIN_FILENO);
		// handle_env_variables(input);
		// validate_input(input); // template for validating
		if (input == NULL)
		{
			printf("\nExiting shell...\n");
			break ;
		}
		if (input[0] == 3)
		{
			printf("\nminishell$> ");
			continue ;
		}
		list = lexer(input);
		print_tokens(list);
		ast_node = parse_tokens(list);
		if (ast_node == NULL)
		{
			printf("Syntax error\n");
			continue ;
		}
		display_ast(ast_node, 0);
		execute_ast(ast_node);
		write(STDOUT_FILENO, "Entered: ", 9);
		write(STDOUT_FILENO, input, ft_strlen(input));
		free(input);
		ft_lstclear(&list, free_list);
	}
}
