/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 17:47:56 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/26 23:56:10 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_env_vars(char	**envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

void	clear_copy(char **copy)
{
	int	i;

	i = 0;
	while (copy[i])
	{
		free(copy[i]);
		i++;
	}
	free(copy);
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
