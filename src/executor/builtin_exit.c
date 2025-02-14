/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 13:30:33 by iasonov           #+#    #+#             */
/*   Updated: 2025/02/14 18:18:13 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_exit(t_state *state)
{
	reset_state(state);
	free_envp_list(state);
	free(state);
	rl_clear_history();
	ft_write("Exiting minishell\n", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}
