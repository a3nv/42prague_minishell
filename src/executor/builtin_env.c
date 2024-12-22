/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 19:55:13 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/22 20:32:29 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_env(t_state *state)
{
	char	**venv;
	int		i;

	i = 0;
	venv = state->envp;
	while (venv[i] != NULL)
	{
		ft_write(venv[i], STDOUT_FILENO);
		ft_write("\n", STDOUT_FILENO);
		i++;
	}
}
