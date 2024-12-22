/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:56:32 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/22 13:16:34 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

const char	*get_token_type_name(t_token_type type)
{
	const char	*token_type_names[7];

	token_type_names[0] = "WORD";
	token_type_names[1] = "PIPE";
	token_type_names[2] = "REDIRECT_IN";
	token_type_names[3] = "REDIRECT_OUT";
	token_type_names[4] = "REDIRECT_APPEND";
	token_type_names[5] = "REDIRECT_HEREDOC";
	token_type_names[6] = "TOKEN_ENV_VAR";
	if (type >= 0 && type < 7)
		return (token_type_names[type]);
	return ("UNKNOWN");
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
			Type: \033[0;35m %-18s \033[0m \n",
			token->value,
			get_token_type_name(token->type));
		printf("--------------------------------------------------\n");
		current = current->next;
	}
}
