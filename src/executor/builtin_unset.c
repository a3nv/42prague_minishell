/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 20:43:25 by iasonov           #+#    #+#             */
/*   Updated: 2025/01/05 15:43:18 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

void	builtin_unset(t_ast_node *node, t_state *state)
{
	int		i;

	i = 0;
	while (node->args[++i])
		array_list_remove(state->envp_list, node->args[i]);
}
