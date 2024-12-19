/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 23:28:11 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/19 22:59:49 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
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
	if (DEBUG_MODE)
		display_ast(ast_node, 0);
	return (ast_node);
}

void	print_debug_info(void)
{
	if (!DEBUG_MODE)
		printf("Debug mode is disabled. DEBUG_MODE = %d.\n", DEBUG_MODE);
	else
		printf("Debug mode is enabled. DEBUG_MODE = %d.\n", DEBUG_MODE);
}

int	main(int argc, char *argv[])
{
	char		*input;
	t_list		*list;
	t_ast_node	*ast_node;

	(void)argc;
	(void)argv;
	print_debug_info();
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
		if (DEBUG_MODE)
		{
			write(STDOUT_FILENO, "Entered: ", 9);
			write(STDOUT_FILENO, input, ft_strlen(input));
		}
		free(input);
		ft_lstclear(&list, free_list);
	}
}
