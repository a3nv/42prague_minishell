/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:25:54 by iasonov           #+#    #+#             */
/*   Updated: 2025/01/03 18:35:06 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * This file contains functions related to the creation of the envp array from 
 * envp_map.
 */
#include "../../includes/minishell.h"

void	free_envp(t_state *state)
{
	int	i;

	if (!state->envp)
		return ;
	i = -1;
	while (state->envp[++i])
		free(state->envp[i]);
	free(state->envp);
}

void	copy_from_list(char **nenvp, t_hashmap_entry *entry, size_t *i)
{
	char	buffer[1024];

	while (entry != NULL)
	{
		ft_str_builder(buffer, sizeof(buffer), entry->key, "=",
			entry->value, NULL);
		nenvp[*i] = ft_strdup(buffer);
		if (!nenvp[*i])
		{
			while (*i > 0)
				free(nenvp[--(*i)]);
			free(nenvp);
			perror("Failed to allocate memory for environment variable");
			exit(EXIT_FAILURE);
		}
		(*i)++;
		entry = entry->next;
	}
}

/*
 * Allcoates memory and fills it with values of t_hashmap.
 */
char	**generate_envp_from_map(t_hashmap *map)
{
	char			**nenvp;
	size_t			i;
	size_t			j;
	t_hashmap_entry	*entry;

	nenvp = malloc((map->count + 1) * sizeof(char *));
	if (!nenvp)
		return (NULL);
	i = 0;
	j = 0;
	while (j < map->count)
	{
		entry = map->entries[j];
		copy_from_list(nenvp, entry, &i);
		j++;
	}
	nenvp[i] = NULL;
	return (nenvp);
}

/*
 * Update envp array from map. Caleld from export and unset functions
 */
void	update_envp(t_state *state)
{
	char	**new_envp;

	new_envp = generate_envp_from_map(state->envp_map);
	if (!new_envp)
	{
		perror("Failed to allocate new environment");
		exit(EXIT_FAILURE);
	}
	if (state->is_envp_dynamic && state->envp)
		free_envp(state);
	state->envp = new_envp;
	state->is_envp_dynamic = true;
}
