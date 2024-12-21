/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 23:17:21 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/21 23:35:21 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_cd(t_ast_node *node)
{
	if (node->argc < 2)
	{
		write(STDERR_FILENO, "cd: Missing argument\n", 21);
		return ;
	}
	if (node->argc > 2)
	{
		write(STDERR_FILENO, "cd: too many arguments\n", 24);
		return ;
	}
	if (chdir(node->args[1]) != 0)
	{
		perror("cd");
	}
}
