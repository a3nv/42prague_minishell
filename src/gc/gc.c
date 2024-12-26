/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 13:04:47 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/26 23:52:00 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_list(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	if (token->value)
		free(token->value);
	free(token);
}

void	free_ast(t_ast_node *root_node)
{
	if (!root_node)
		return ;
	free_ast(root_node->left);
	free_ast(root_node->right);
	free(root_node);
}

void	reset_state(t_state *state)
{
	if (state->input)
		free(state->input);
	if (state->token_list)
		ft_lstclear(&state->token_list, free_list);
	if (state->root_node)
		free_ast(state->root_node);
}
