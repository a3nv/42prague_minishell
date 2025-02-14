/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 13:04:47 by iasonov           #+#    #+#             */
/*   Updated: 2025/02/14 22:48:47 by iasonov          ###   ########.fr       */
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

void	free_ast(t_ast_node *node)
{
	int	i;

	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->args)
	{
		i = 0;
		while (node->args[i])
		{
			free(node->args[i]);
			i++;
		}
		free(node->args);
	}
	if (node->redirection.infile)
		free(node->redirection.infile);
	if (node->redirection.outfile)
		free(node->redirection.outfile);
	if (node->redirection.heredoc_delim)
		free(node->redirection.heredoc_delim);
	free(node);
}

void	free_envp_list(t_state *state)
{
	if (state->envp_list)
	{
		array_list_free(state->envp_list);
		state->envp_list = NULL;
	}
}

void	reset_state(t_state *state)
{
	if (state->input)
	{
		free(state->input);
		state->input = NULL;
	}
	if (state->token_list)
	{
		ft_lstclear(&state->token_list, free_list);
		state->token_list = NULL;
	}
	if (state->root_node)
	{
		free_ast(state->root_node);
		state->root_node = NULL;
	}
	if (state->current_node)
	{
		free_ast(state->current_node);
		state->current_node = NULL;
	}
}
