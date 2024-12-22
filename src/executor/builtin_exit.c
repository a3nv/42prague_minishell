/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 13:30:33 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/22 13:31:45 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_exit(t_state *state)
{
	free_state(state);
	ft_write("Exiting minishell\n", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}
