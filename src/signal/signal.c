/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 19:34:13 by iasonov           #+#    #+#             */
/*   Updated: 2025/02/14 19:54:28 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_sigint(int sig)
{
	(void) sig;
	g_reset_requested = 1;
	ft_write("\nminishell>", STDOUT_FILENO);
}

void	handle_sigquit(int sig)
{
	(void) sig;
}

void	register_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}
