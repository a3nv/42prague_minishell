/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_list_add.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:33:41 by iasonov           #+#    #+#             */
/*   Updated: 2025/02/20 21:39:35 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	realloc_list(t_array_list *list)
{
	char	**new_data;
	int		new_capacity;

	new_capacity = list->capacity * 2;
	new_data = malloc((new_capacity + 1) * sizeof(char *));
	if (!new_data)
		return ;
	ft_memcpy(new_data, list->data, list->size * sizeof(char *));
	new_data[list->size] = NULL;
	free(list->data);
	list->data = new_data;
	list->capacity = new_capacity;
}

void	array_list_add(t_array_list *list, char *element)
{
	if (!list || !list->data || !element)
		return ;
	if (list->size >= list->capacity)
		realloc_list(list);
	list->data[list->size] = ft_strdup(element);
	if (!list->data[list->size])
	{
		ft_write("Error: Failed to allocate memory for element: %s\n",
			STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	list->size++;
	list->data[list->size] = NULL;
}
