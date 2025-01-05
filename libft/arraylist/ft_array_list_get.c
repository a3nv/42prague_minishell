/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_list_get.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:30:47 by iasonov           #+#    #+#             */
/*   Updated: 2025/01/05 18:15:46 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*array_list_get(t_array_list *list, char *key)
{
	int	matched_index;

	matched_index = find_matched_key(key, list->data);
	return (list->data[matched_index]);
}

char	*array_list_get_env_value(t_array_list *list, char *key)
{
	char	*entry;
	char	*value;
	t_pair	*pair;

	entry = array_list_get(list, key);
	if (!entry)
		return (NULL);
	pair = parse_arg(entry);
	if (!pair)
		return (NULL);
	value = ft_strdup(pair->second);
	free_pair(pair);
	return (value);
}
