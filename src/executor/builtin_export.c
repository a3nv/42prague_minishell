/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 20:25:58 by iasonov           #+#    #+#             */
/*   Updated: 2025/01/02 20:28:35 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

void	builtin_export(t_ast_node *node, t_state *state)
{
	int		i;
	char	*arg;
	t_pair	*pair;

	i = 1;
	arg = node->args[i];
	while (arg)
	{
		pair = parse_arg(arg);
		ft_hashmap_insert(state->envp_map, pair->first, pair->second);
		free(pair);
		i++;
		arg = node->args[i];
	}
	update_envp(state);
}
