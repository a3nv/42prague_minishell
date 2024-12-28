/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:20:47 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/28 22:55:13 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

unsigned int	ft_hash(const char *key, size_t size)
{
	unsigned long int	value;

	value = 0;
	while (*key != '\0')
	{
		value = value * PRIME_MULTIPLIER + *key;
		key++;
	}
	return (value % size);
}

void	ft_hashmap_free(t_hashmap *map)
{
	t_hashmap_entry	*entry;
	t_hashmap_entry	*temp;
	size_t			i;

	i = -1;
	while (++i < map->size)
	{
		entry = map->entries[i];
		while (entry != NULL)
		{
			temp = entry;
			entry = entry-> next;
			free(temp->key);
			free(temp->value);
			free(temp);
		}
	}
	free(map->entries);
	free(map);
}
