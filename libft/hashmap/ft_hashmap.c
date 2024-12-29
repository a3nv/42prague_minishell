/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:35:09 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/29 22:59:37 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_hashmap	*ft_hashmap_create(size_t size)
{
	t_hashmap	*map;
	size_t		i;

	if (size == 0 || size > MAX_HASHMAP_SIZE)
		return (NULL);
	map = malloc(sizeof(t_hashmap));
	if (map == NULL)
		return (NULL);
	map->size = size;
	map->entries = malloc(sizeof(t_hashmap_entry *) * size);
	if (map->entries == NULL)
	{
		free(map);
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		map->entries[i] = NULL;
		i++;
	}
	return (map);
}

t_hashmap_entry	*ft_hashmap_get_entry(t_hashmap *map, const char *key)
{
	unsigned int	index;
	t_hashmap_entry	*entry;

	if (!map || !key)
		return (NULL);
	index = ft_hash(key, map->size);
	entry = map->entries[index];
	while (entry != NULL)
	{
		if (ft_strcmp(entry->key, key) == 0)
		{
			return (entry);
		}
		entry = entry->next;
	}
	return (NULL);
}

char	*ft_hashmap_get_value(t_hashmap *map, const char *key)
{
	t_hashmap_entry	*entry;

	if (!map || !key)
		return (NULL);
	entry = ft_hashmap_get_entry(map, key);
	if (!entry)
		return (NULL);
	return (entry->value);
}

void	free_entry(t_hashmap_entry *entry)
{
	free(entry->key);
	free(entry->value);
	free(entry);
}

void	ft_hashmap_remove(t_hashmap *map, char *key)
{
	int				index;
	t_hashmap_entry	*entry;
	t_hashmap_entry	*prev;

	if (!map || !key)
		return ;
	prev = NULL;
	index = ft_hash(key, map->size);
	entry = map->entries[index];
	while (entry)
	{
		if (ft_strcmp(entry->key, key) == 0)
		{
			if (prev == NULL)
				map->entries[index] = entry->next;
			else
				prev->next = entry->next;
			free_entry(entry);
			map->count--;
			return ;
		}
		prev = entry;
		entry = entry->next;
	}
}
