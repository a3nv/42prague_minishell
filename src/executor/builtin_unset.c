/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 20:43:25 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/27 22:11:39 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

void	remove_env(int matched_index, char ***envp)
{
	int	i;
	int	count;

	count = 0;
	while ((*envp)[count] != NULL)
		count++;
	free((*envp)[matched_index]);
	i = matched_index;
	while (i < count - 1)
	{
		(*envp)[i] = (*envp)[i + 1];
		i++;
	}
	(*envp)[count - 1] = NULL;
}

void	builtin_unset(t_ast_node *node, t_state *state)
{
	int		i;
	int		match;
	char	*arg;

	i = 1;
	arg = node->args[i];
	while (arg)
	{
		match = find_matched_key(arg, state->envp);
		if (match != -1)
			remove_env(match, &state->envp);
		i++;
		arg = node->args[i];
	}
}
