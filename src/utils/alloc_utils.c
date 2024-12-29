/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 13:01:18 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/29 22:44:37 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	init_map_with_env(t_hashmap **map, char **envp)
{
	int		i;
	t_pair	*pair;

	i = -1;
	while (envp[++i])
	{
		pair = parse_arg(envp[i]);
		ft_hashmap_insert(*map, pair->first, pair->second);
		free(pair);
	}
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
	state->envp = envp;
	env_count = count_env_vars(envp);
	if (env_count <= 0)
		ft_write("No environment varaibles found\n", STDOUT_FILENO);
	state->envp_map = ft_hashmap_create(env_count);
	if (!state->envp_map)
		ft_write("Failed to create map", STDOUT_FILENO);
	init_map_with_env(&state->envp_map, envp);
	return (state);
}
