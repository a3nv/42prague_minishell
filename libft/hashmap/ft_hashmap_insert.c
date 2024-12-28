/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashmap_insert.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:35:09 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/28 22:54:37 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_hashmap_replace(t_hashmap *map, const char *key, const char *value)
{
	unsigned int	index;
	t_hashmap_entry	*entry;

	if (!map || !key || !value)
		return (-1);
	index = ft_hash(key, map->size);
	entry = map->entries[index];
	while (entry != NULL)
	{
		if (ft_strcmp(entry->key, key) == 0)
		{
			free(entry->value);
			entry->value = ft_strdup(value);
			if (entry->value)
				return (0);
			else
				return (-1);
		}
		entry = entry->next;
	}
	return (-1);
}

int	ft_hashmap_insert_new(t_hashmap *map, const char *key, const char *value)
{
	unsigned int	index;
	t_hashmap_entry	*entry;

	if (!map || !key || !value)
		return (-1);
	entry = malloc(sizeof(t_hashmap_entry));
	if (entry == NULL)
		return (-1);
	entry->key = ft_strdup(key);
	entry->value = ft_strdup(value);
	if (!entry->key || !entry->value)
	{
		free(entry->key);
		free(entry->value);
		free(entry);
		return (-1);
	}
	index = ft_hash(key, map->size);
	entry->next = map->entries[index];
	map->entries[index] = entry;
	return (0);
}

int	ft_hashmap_insert(t_hashmap *map, const char *key, const char *value)
{
	if (ft_hashmap_replace(map, key, value) == 0)
		return (0);
	return (ft_hashmap_insert_new(map, key, value));
}
