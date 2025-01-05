/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 20:25:58 by iasonov           #+#    #+#             */
/*   Updated: 2025/01/05 14:41:31 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

void	builtin_export(t_ast_node *node, t_state *state)
{
	int		i;

	i = 0;
	while (node->args[++i])
		array_list_add(state->envp_list, node->args[i]);
}
