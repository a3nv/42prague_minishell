/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 20:25:58 by iasonov           #+#    #+#             */
/*   Updated: 2025/02/20 22:25:42 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>
#include <unistd.h>

void	print_export_error(char *arg)
{
	ft_write("minishell: export: ", STDOUT_FILENO);
	ft_write(arg, STDOUT_FILENO);
	ft_write(": not a valid identifier\n", STDOUT_FILENO);
}

int	is_valid(t_pair *pair)
{
	char	*p;

	p = pair->first;
	while (*p)
	{
		if (!ft_isalnum(*p))
			return (0);
		p++;
	}
	return (1);
}

void	builtin_export(t_ast_node *node, t_state *state)
{
	int		i;
	int		matched_index;
	t_pair	*pair;

	i = 0;
	while (node->args[++i])
	{
		pair = parse_arg(node->args[i]);
		if (!pair)
			continue ;
		if (!is_valid(pair))
		{
			print_export_error(node->args[i]);
			continue ;
		}
		matched_index = find_matched_key(pair->first, state->envp_list->data);
		if (matched_index == -1)
			array_list_add(state->envp_list, node->args[i]);
		else
		{
			free(state->envp_list->data[matched_index]);
			state->envp_list->data[matched_index] = ft_strdup(node->args[i]);
		}
		free_pair(pair);
	}
}
