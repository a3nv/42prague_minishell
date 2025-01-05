/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_list_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:33:41 by iasonov           #+#    #+#             */
/*   Updated: 2025/01/05 14:32:17 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdlib.h>

void	realloc_list(array_list *list)
{
	char	**new_data;

	new_data = malloc((list->capacity * 2) * sizeof(char *));
	if (!new_data)
		return ;
	ft_memcpy(new_data, list->data, list->size * sizeof(char *));
	free(list->data);
	list->data = new_data;
	list->capacity *= 2;
}

void	array_list_add(array_list *list, char *element)
{
	if (list->size >= list->capacity)
		realloc_list(list);
	list->data[list->size] = ft_strdup(element); 
	list->size++;
}
