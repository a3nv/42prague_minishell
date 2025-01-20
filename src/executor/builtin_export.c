/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 20:25:58 by iasonov           #+#    #+#             */
/*   Updated: 2025/01/17 23:56:27 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

void	builtin_export(t_ast_node *node, t_state *state)
{
	int		i;
	int		matched_index;
	t_pair	*pair;

	i = 0;
	while (node->args[++i])
	{
		pair = parse_arg(node->args[i]);
		if (!pair)
			continue ;
		matched_index = find_matched_key(pair->first, state->envp_list->data);
		if (matched_index == -1)
			array_list_add(state->envp_list, node->args[i]);
		else
		{
			free(state->envp_list->data[matched_index]);
			state->envp_list->data[matched_index] = ft_strdup(node->args[i]);
		}
		free_pair(pair);
	}
}
