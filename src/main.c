/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 23:28:11 by iasonov           #+#    #+#             */
/*   Updated: 2025/02/06 21:52:19 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*read_input(void)
{
	char	*input;

	input = readline("minishell>");
	if (input == NULL)
	{
		printf("\nExiting minishell...\n");
		exit(EXIT_FAILURE);
	}
	add_history(input);
	return (input);
}

t_ast_node	*transform_list(t_state *state)
{
	t_ast_node	*ast_node;

	ast_node = parse_tokens(state);
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

	validate_args(argc, argv);
	print_debug_info();
	register_signals();
	state = init(envp);
	while (1)
	{
		state->input = read_input();
		state->token_list = lexer(state->input);
		print_tokens(state->token_list);
		state->root_node = transform_list(state);
		if (!state->root_node)
			continue ;
		execute_ast(state->root_node, state);
		if (DEBUG_MODE)
		{
			ft_write("Entered: ", STDOUT_FILENO);
			ft_write(state->input, STDOUT_FILENO);
		}
		reset_state(state);
	}
	clear_history();
	return (0);
}
