/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 00:27:12 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/27 22:51:37 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_env(t_pair *pair, char ***envp)
{
	int		envp_len;
	int		entry_len;
	char	**nenvp;

	nenvp = copy_envp(*envp);
	envp_len = count_env_vars(*envp);
	entry_len = ft_strlen(pair->first) + ft_strlen(pair->second) + 2;
	nenvp[envp_len] = malloc(entry_len);
	if (!nenvp[envp_len])
	{
		clear_copy(nenvp);
		return ;
	}
	ft_str_builder(nenvp[envp_len], entry_len, pair->first, "=",
		pair->second, NULL);
	nenvp[envp_len + 1] = NULL;
	envp_len = 0;
	*envp = nenvp;
}

void	update_env(t_pair *new_env, char ***envp, int mathed_index)
{
	char	*new_arg;
	int		new_len;

	new_len = ft_strlen(new_env->first) + ft_strlen(new_env->second) + 2;
	new_arg = malloc(new_len);
	ft_str_builder(new_arg, new_len, new_env->first, "=",
		new_env->second, NULL);
	free(envp[mathed_index]);
	(*envp)[mathed_index] = new_arg;
}

/**
 * todo: clear pair after use
 */
void	builtin_export(t_ast_node *node, t_state *state)
{
	int		i;
	int		match;
	char	*arg;
	t_pair	*pair;

	i = 1;
	arg = node->args[i];
	while (arg)
	{
		pair = parse_arg(arg);
		match = find_matched_key(pair->first, state->envp);
		if (match == -1)
			add_env(pair, &state->envp);
		else
			update_env(pair, &state->envp, match);
		i++;
		arg = node->args[i];
	}
}
