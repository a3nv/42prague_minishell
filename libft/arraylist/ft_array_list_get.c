/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_list_get.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:30:47 by iasonov           #+#    #+#             */
/*   Updated: 2025/02/20 21:18:32 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * todo: both key an value might be NULL handle this
 */
t_pair	*parse_arg(char *arg)
{
	char	*separator_pt;
	long	key_index;
	char	*key;
	char	*value;

	separator_pt = ft_strchr(arg, '=');
	if (!separator_pt)
		return (NULL);
	key_index = separator_pt - arg;
	key = ft_strndup(arg, key_index);
	value = ft_strdup(separator_pt + 1);
	return (create_pair(key, value));
}

char	*array_list_get(t_array_list *list, char *key)
{
	int	matched_index;

	matched_index = find_matched_key(key, list->data);
	if (matched_index == -1)
		return (NULL);
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
