/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_list_create.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:17:08 by iasonov           #+#    #+#             */
/*   Updated: 2025/01/07 00:01:01 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stddef.h>

t_array_list	*array_list_create(size_t initial_capacity)
{
	t_array_list	*list;
	size_t			i;

	list = malloc(sizeof(t_array_list));
	if (!list)
		return (NULL);
	list->data = malloc((initial_capacity + 1) * sizeof(char *));
	if (!list->data)
	{
		free(list);
		return (NULL);
	}
	i = 0;
	while (i <= initial_capacity)
	{
		list->data[i] = NULL;
		i++;
	}
	list->size = 0;
	list->capacity = initial_capacity;
	return (list);
}
