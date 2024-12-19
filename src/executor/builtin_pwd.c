/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:33:45 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/19 22:46:53 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		if (write(STDOUT_FILENO, cwd, ft_strlen(cwd)) == -1
			|| write(STDOUT_FILENO, "\n", 1) == -1)
			perror("write");
	}
	else
		perror("pwd");
}
