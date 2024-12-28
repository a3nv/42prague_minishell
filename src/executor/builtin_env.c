/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 19:55:13 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/28 22:55:46 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_map(t_hashmap_entry *entry)
{
	if (!entry)
		return ;
	ft_write(entry->key, STDOUT_FILENO);
	ft_write("=", STDOUT_FILENO);
	ft_write(entry->value, STDOUT_FILENO);
	ft_write("\n", STDOUT_FILENO);
}

void	builtin_env(t_state *state)
{
	ft_hashmap_iteri(state->envp_map, print_map);
}
