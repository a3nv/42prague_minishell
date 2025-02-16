/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 23:28:11 by iasonov           #+#    #+#             */
/*   Updated: 2025/02/16 14:10:20 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

volatile sig_atomic_t	g_reset_requested;

char	*read_input(t_state *state)
{
	char	*input;
	char	*trimmed;

	input = readline("minishell>");
	if (input == NULL)
	{
		printf("\nExiting minishell...\n");
		reset_state(state);
		free_envp_list(state);
		free(state);
		rl_clear_history();
		exit(EXIT_FAILURE);
	}
	trimmed = ft_strtrim(input, " \t\n");
	free(input);
	if (!trimmed || ft_strlen(trimmed) == 0)
	{
		free(trimmed);
		return (NULL);
	}
	add_history(trimmed);
	g_reset_requested = 0;
	return (trimmed);
}

void	reset_by_request(t_state *state)
{
	reset_state(state);
	g_reset_requested = 0;
}

void	loop(t_state *state)
{
	while (1)
	{
		state->input = read_input(state);
		if (g_reset_requested)
			reset_by_request(state);
		if (!state->input)
			continue ;
		state->token_list = lexer(state->input);
		if (validate_tokens(state->token_list))
		{
			reset_state(state);
			continue ;
		}
		print_tokens(state->token_list);
		state->root_node = transform_list(state);
		if (!state->root_node)
		{
			reset_state(state);
			continue ;
		}
		execute_ast(state->root_node, state);
		reset_state(state);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_state		*state;

	validate_args(argc, argv);
	register_signals();
	state = init(envp);
	loop(state);
	free_envp_list(state);
	rl_clear_history();
	return (0);
}
