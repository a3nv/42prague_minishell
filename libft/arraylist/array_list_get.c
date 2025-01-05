/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_list_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:30:47 by iasonov           #+#    #+#             */
/*   Updated: 2025/01/05 17:35:03 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*array_list_get(array_list *list, char *key)
{
	int	matched_index;

	matched_index = find_matched_key(key, list->data);
	return (list->data[matched_index]);
}

char	*array_list_get_env_value(array_list *list, char *key)
{
	char	*entry;
	t_pair	*pair;

	entry = array_list_get(list, key);
	pair = parse_arg(entry);
	return (pair->second);
}
