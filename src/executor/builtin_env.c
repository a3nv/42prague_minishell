/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 19:55:13 by iasonov           #+#    #+#             */
/*   Updated: 2025/01/05 15:43:12 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_env(t_state *state)
{
	int	i;

	i = -1;
	while (state->envp_list->data[++i])
	{
		ft_write(state->envp_list->data[i], STDOUT_FILENO);
		ft_write("\n", STDOUT_FILENO);
	}
}
