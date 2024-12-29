/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 20:43:25 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/29 22:49:43 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

void	builtin_unset(t_ast_node *node, t_state *state)
{
	int		i;
	char	*arg;

	i = 1;
	arg = node->args[i];
	while (arg)
	{
		ft_hashmap_remove(state->envp_map, arg);
		i++;
		arg = node->args[i];
	}
}
