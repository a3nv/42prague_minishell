/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_iteri.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 18:04:33 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/28 22:55:03 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stddef.h>

void	ft_hashmap_iteri(t_hashmap *map, void (*f)(t_hashmap_entry *entry))
{
	size_t			i;
	t_hashmap_entry	*entry;

	if (!map || !map->entries || !f)
		return ;
	i = -1;
	while (++i < map->size)
	{
		entry = map->entries[i];
		while (entry != NULL)
		{
			f(entry);
			entry = entry->next;
		}
	}
}
