/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 20:44:26 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/27 20:49:15 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_matched_key(char *key, char **envp)
{
	int	i;
	int	key_len;

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
