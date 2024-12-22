/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 23:17:21 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/22 12:23:41 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_cd(t_ast_node *node)
{
	if (node->argc < 2)
	{
		ft_write("cd: missing argument\n", STDERR_FILENO);
		return ;
	}
	if (node->argc > 2)
	{
		ft_write("cd: too many arguments\n", STDERR_FILENO);
		return ;
	}
	if (chdir(node->args[1]) != 0)
	{
		perror("cd");
	}
}
