/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 13:01:18 by iasonov           #+#    #+#             */
/*   Updated: 2025/01/05 22:05:22 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * This is a helper fucntion to init the state struct when starting the 
 * programm
 */
#include "../../includes/minishell.h"

void	init_list_with_env(char	**envp, t_state *state, int env_count)
{
	int	i;

	state->envp_list = array_list_create(env_count);
	i = -1;
	while (envp[++i])
		array_list_add(state->envp_list, envp[i]);
}

t_state	*init(char **envp)
{
	t_state	*state;
	int		env_count;

	state = malloc(sizeof(t_state));
	if (!state)
	{
		perror("Failed to allocate shell state");
		exit(EXIT_FAILURE);
	}
	state->input = NULL;
	state->token_list = NULL;
	state->root_node = NULL;
	state->current_node = NULL;
	env_count = count_env_vars(envp);
	if (env_count <= 0)
		ft_write("No environment varaibles found\n", STDOUT_FILENO);
	init_list_with_env(envp, state, env_count);
	return (state);
}
