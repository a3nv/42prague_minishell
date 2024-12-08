/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 23:28:11 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/07 17:23:39 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

const char	*get_token_type_name(t_token_type type)
{
	const char	*token_type_names[7];

	token_type_names[0] = "WORD";
	token_type_names[1] = "PIPE";
	token_type_names[2] = "REDIRECT_IN";
	token_type_names[3] = "REDIRECT_OUT";
	token_type_names[4] = "REDIRECT_APPEND";
	token_type_names[5] = "REDIRECT_HEREDOC";
	token_type_names[6] = "TOKEN_ENV_VAR";
	if (type >= 0 && type < 7)
		return (token_type_names[type]);
	return ("UNKNOWN");
}

void	free_list(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	if (token->value)
		free(token->value);
	free(token);
}

void	print_tokens(t_list *lexer)
{
	t_list	*current;
	t_token	*token;

	current = lexer;
	while (current)
	{
		token = current->content;
		printf("Token: \033[0;36m %-20s \033[0m |\t \
			Type: \033[0;35m %-18s \033[0m \n",
				token->value,
				get_token_type_name(token->type));
		printf("--------------------------------------------------\n");
		current = current->next;
	}
}

void	print_node(t_ast_node *node)
{
	if (node->type == NODE_COMMAND)
		printf("└── Node Type: WORD, Token Value: %s\n", node->value);
	else if (node->type == NODE_PIPE)
		printf("└── Node Type: PIPE\n");
	else if (node->type == NODE_REDIRECTION)
		printf("└── Node Type: REDIRECT IN\n");
	// else if (node->type == TOKEN_REDIR_OUT)
	//	printf("└── Node Type: REDIRECT OUT\n");
	// else if (node->type == TOKEN_REDIR_APPEND)
	//	printf("└── Node Type: REDIRECT APPEND\n");
	// else if (node->type == TOKEN_REDIR_HEREDOC)
	//	printf("└── Node Type: REDIRECT HEREDOC\n");
	else
		printf("└── Node Type: UNKNOWN\n");
}

void	display_ast(t_ast_node *node, int depth)
{
	int	i;

	i = 0;
	if (node == NULL)
		return ;
	display_ast(node->left, depth + 1);
	while (i++ < depth)
		printf("	");
	print_node(node);
	display_ast(node->right, depth + 1);
}

int	main(void)
{
	char		*input;
	t_list		*list;
	t_ast_node	*ast_node;

	while (1)
	{
		write(STDOUT_FILENO, "minishell$> ", 11);
		input = get_next_line(STDIN_FILENO);
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
		if (parse_tokens(list) != 0)
		{
			printf("Syntax error\n");
		}
		print_tokens(list);
		ast_node = parse_tokens(list);
		display_ast(ast_node, 0);
		write(STDOUT_FILENO, "Entered: ", 9);
		write(STDOUT_FILENO, input, ft_strlen(input));
		ast_node = parse_tokens(list);
		// int i = 0; // Initialize index for commands
		// while (command->commands[i]) {
		// 	write(STDOUT_FILENO, "Command ", 8);
		// 	char command_index[10];
		// 	sprintf(command_index, "%d", i + 1); // Convert index to string
		// 	write(STDOUT_FILENO, command_index, strlen(command_index));
		// 	write(STDOUT_FILENO, ":\n", 2);
		//
		// 	int j = 0; // Initialize index for arguments
		// 	while (command->commands[i]->arguments[j]) {
		// 		char *arg = command->commands[i]->arguments[j];
		// 		write(STDOUT_FILENO, "  Transformed arg: ", 19);
		// 		write(STDOUT_FILENO, arg, strlen(arg));
		// 		write(STDOUT_FILENO, "\n", 1); // Add newline for readability
		// 		j++;
		// 	}
		// 	write(STDOUT_FILENO, "\n", 1); // Separate commands for clarity
		// 	i++;
		// }
		free(input);
		ft_lstclear(&list, free_list);
	}
}
