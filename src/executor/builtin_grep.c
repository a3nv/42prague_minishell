/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_grep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 12:24:27 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/31 13:31:44 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_grep(t_ast_node *node)
{
	char	*line;

	if (!node || !node->args[1])
	{
		ft_write("grep: missing pattern\n", STDOUT_FILENO);
	}
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (ft_strnstr(line, node->args[1], ft_strlen(line)))
			ft_write(line, STDOUT_FILENO);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
}
