/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 23:28:11 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/18 00:09:48 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

char	*read_input(void)
{
	char	*input;

	input = get_next_line(STDIN_FILENO);
	if (input == NULL)
	{
		printf("\nExiting shell...\n");
		exit(EXIT_FAILURE);
	}
	return (input);
}

t_ast_node	*transform_list(t_list *list)
{
	t_ast_node	*ast_node;

	ast_node = parse_tokens(list);
	if (ast_node == NULL)
	{
		printf("Syntax error\n");
		return (NULL);
	}
	display_ast(ast_node, 0);
	return (ast_node);
}

int	main(int argc, char *argv[])
{
	char		*input;
	t_list		*list;
	t_ast_node	*ast_node;

	(void)argc;
	(void)argv;
	while (1)
	{
		write(STDOUT_FILENO, "minishell$> ", 11);
		input = read_input();
		list = lexer(input);
		print_tokens(list);
		ast_node = transform_list(list);
		if (!ast_node)
			continue ;
		execute_ast(ast_node);
		write(STDOUT_FILENO, "Entered: ", 9);
		write(STDOUT_FILENO, input, ft_strlen(input));
		free(input);
		ft_lstclear(&list, free_list);
	}
}
