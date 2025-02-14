/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:59:59 by iasonov           #+#    #+#             */
/*   Updated: 2025/02/14 15:22:14 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	validate_args(int argc, char **argv)
{
	(void) argv;
	if (argc != 1)
	{
		ft_write("Error: minishell does not accept any arguments\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
	{
		ft_write("Error: minishell must be run interactively\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

void	validate_input_(char *input)
{
	(void) input;
}
