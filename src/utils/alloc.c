/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 13:01:18 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/22 19:54:53 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_state	*init(char **envp)
{
	t_state	*state;

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
	return (state);
}
