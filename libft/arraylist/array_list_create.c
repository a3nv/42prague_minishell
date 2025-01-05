/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_list_create.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:17:08 by iasonov           #+#    #+#             */
/*   Updated: 2025/01/05 14:32:31 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

array_list	*array_list_create(size_t initial_capacity)
{
	array_list *list;

	list = malloc(sizeof(array_list));
	if (!list)
		return (NULL);
	list->data = malloc(sizeof(char *) * initial_capacity + 1);
	if (!list->data)
		return (NULL);
	list->data[initial_capacity + 1] = NULL;
	list->size = 0;
	list->capacity = initial_capacity;
	return (list);
}
