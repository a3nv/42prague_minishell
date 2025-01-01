/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_wc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 12:54:49 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/31 13:07:42 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stddef.h>

void	builtin_wc(void)
{
	char	*line;
	int		line_count;

	line_count = 0;
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		line_count++;
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	ft_putnbr_fd(line_count, STDOUT_FILENO);
	ft_write("\n", STDOUT_FILENO);
}
