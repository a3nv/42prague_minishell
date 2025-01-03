/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 22:46:03 by iasonov           #+#    #+#             */
/*   Updated: 2025/01/02 00:44:28 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(t_ast_node *node)
{
	char	*builtin_commands[9];
	int		count;
	int		i;

	if (!node || node->type != NODE_COMMAND || !node->args)
		return (0);
	builtin_commands[0] = "cd";
	builtin_commands[1] = "echo";
	builtin_commands[2] = "env";
	builtin_commands[3] = "exit";
	builtin_commands[4] = "export";
	builtin_commands[5] = "grep";
	builtin_commands[6] = "pwd";
	builtin_commands[7] = "unset";
	builtin_commands[8] = "wc";
	count = sizeof(builtin_commands) / sizeof(builtin_commands[0]);
	i = 0;
	while (i < count)
	{
		if (ft_strcmp(builtin_commands[i], node->args[0]) == 0)
			return (1);
		i++;
	}
	return (0);
}
