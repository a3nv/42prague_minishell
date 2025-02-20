/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command_node.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:51:27 by iasonov           #+#    #+#             */
/*   Updated: 2025/02/20 21:11:19 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void append_argument(t_ast_node *node, char *new_arg)
{
	int current_argc = node->argc;
	char **new_args = realloc(node->args, sizeof(char *) * (current_argc + 2));
	if (!new_args)
	{
		perror("realloc failed");
		exit(EXIT_FAILURE);
	}
	node->args = new_args;
	node->args[current_argc] = new_arg;
	node->args[current_argc + 1] = NULL;
	node->argc = current_argc + 1;
}

char	*expand_env_variable(t_token *token, t_state *state)
{
	char *expanded_value;

	if (token->expandable && ft_strchr(token->value, '$'))
	{
		expanded_value = expand_variable(state, token->value);
		if (!expanded_value)
			expanded_value = ft_strdup("");
	}
	else
		expanded_value = ft_strdup(token->value);
	return (expanded_value);
}

void create_command_node(t_ast_node **cur, t_token *token, t_state *state)
{
	char *expanded_value;

	expanded_value = expand_env_variable(token, state);
	if (*cur && (*cur)->type == NODE_REDIRECTION)
	{
		if (!(*cur)->left)
		{
			(*cur)->left = create_ast_node(NODE_COMMAND, expanded_value);
			free(expanded_value);
		}
		else
			append_argument((*cur)->left, expanded_value);
		return;
	}
	if (*cur)
		append_argument(*cur, expanded_value);
	else
	{
		*cur = create_ast_node(NODE_COMMAND, expanded_value);
		free(expanded_value);
	}
}
