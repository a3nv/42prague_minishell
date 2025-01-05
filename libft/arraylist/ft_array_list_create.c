/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_list_create.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:17:08 by iasonov           #+#    #+#             */
/*   Updated: 2025/01/05 18:03:05 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_array_list	*array_list_create(size_t initial_capacity)
{
	t_array_list *list;

	list = malloc(sizeof(t_array_list));
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
