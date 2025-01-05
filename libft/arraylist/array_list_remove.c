/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_list_remove.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:42:50 by iasonov           #+#    #+#             */
/*   Updated: 2025/01/05 15:29:19 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stddef.h>
#include <stdlib.h>

void	array_list_free(array_list *list)
{
	int	i;

	i = 0;
	while (list->data[i])
	{
		free(list->data[i]);
		i++;
	}
	free(list->data);
	free(list);
}

int	find_matched_key(char *key, char **envp)
{
	int	i;
	int	key_len;

	if (!key || !*key)
		return (-1);
	i = 0;
	key_len = ft_strlen(key);
	while (envp[i])
	{
		if (ft_strncmp(key, envp[i], key_len) == 0 && envp[i][key_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	array_list_remove(array_list *list, char *element)
{
	int	match;
	int	i;

	 if (!list || !element || !list->data)
        return ;
	match = find_matched_key(element, list->data);
	if (match == -1)
		return ;
	free(list->data[match]);
	i = match + 1;
	while (i < list->size)
	{
		list->data[i - 1] = list->data[i];
		i++;
	}
	list->size--;
	list->data[list->size] = NULL;
}
