/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 17:47:56 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/27 20:50:46 by iasonov          ###   ########.fr       */
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

char	**copy_envp(char **original)
{
	int		count;
	int		i;
	char	**nenvp;

	count = count_env_vars(original);
	nenvp = malloc((count + 2) * sizeof(char *));
	if (!nenvp)
		return (NULL);
	i = 0;
	while (original[i])
	{
		nenvp[i] = ft_strdup(original[i]);
		if (!nenvp[i])
		{
			clear_copy(nenvp);
			return (NULL);
		}
		i++;
	}
	return (nenvp);
}
