/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 23:28:11 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/22 19:53:29 by iasonov          ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	t_state		*state;

	(void)argc;
	(void)argv;
	print_debug_info();
	while (1)
	{
		state = init(envp);
		ft_write("minishell$> ", STDOUT_FILENO);
		state->input = read_input();
		state->token_list = lexer(state->input);
		print_tokens(state->token_list);
		state->root_node = transform_list(state->token_list);
		if (!state->root_node)
			continue ;
		execute_ast(state->root_node, state);
		if (DEBUG_MODE)
		{
			ft_write("Entered: ", STDOUT_FILENO);
			ft_write(state->input, STDOUT_FILENO);
		}
		free_state(state);
	}
	return (0);
}
