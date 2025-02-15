/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_printer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:25:08 by iasonov           #+#    #+#             */
/*   Updated: 2025/02/15 21:26:44 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_debug_info(void)
{
	if (!DEBUG_MODE)
		printf("Debug mode is disabled. DEBUG_MODE = %d.\n", DEBUG_MODE);
	else
		printf("Debug mode is enabled. DEBUG_MODE = %d.\n", DEBUG_MODE);
}

void	print_tokens(t_list *lexer)
{
	t_list	*current;
	t_token	*token;

	if (!DEBUG_MODE)
		return ;
	current = lexer;
	while (current)
	{
		token = current->content;
		printf("Token: \033[0;36m %-20s \033[0m |\t \
			Type: \033[0;35m %-18s \033[0m, expandable = %d \n",
			token->value,
			get_token_type_name(token->type), token->expandable);
		printf("--------------------------------------------------\n");
		current = current->next;
	}
}
