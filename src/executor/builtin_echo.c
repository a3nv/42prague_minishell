/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:37:12 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/22 19:06:57 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

void	builtin_echo(t_ast_node *node)
{
	int	new_line;
	int	i;

	new_line = 0;
	i = 1;
	if (node->args[i] && ft_strcmp(node->args[i], "-n") == 0)
	{
		new_line = 1;
		i++;
	}
	while (node->args[i])
	{
		ft_write(node->args[i], STDOUT_FILENO);
		if (node->args[i + 1])
			ft_write(" ", STDOUT_FILENO);
		i++;
	}
	if (new_line)
		ft_write("\n", STDOUT_FILENO);
}
