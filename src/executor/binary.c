/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:33:45 by iasonov           #+#    #+#             */
/*   Updated: 2025/02/16 14:09:11 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * check_path:
 *   Retrieves the PATH variable from the environment list,
 *   splits it into directories, and uses find_accessible_path
 *   to locate the executable. Cleans up allocated memory before
 *   returning.
 */
char	*check_path(char *command, t_array_list *list)
{
	char	*env_path;
	char	**dirs;
	char	*result;

	env_path = array_list_get_env_value(list, "PATH");
	if (!env_path)
		return (NULL);
	dirs = ft_split(env_path, ':');
	free(env_path);
	if (!dirs)
		return (NULL);
	result = find_accessible_path(command, dirs);
	free_dirs(dirs);
	return (result);
}

char	*find_binary_path(char *command, t_array_list *list)
{
	if (!command || !*command)
		return (NULL);
	if (command[0] == '/' || strchr(command, '/'))
	{
		if (access(command, X_OK) == 0)
			return (ft_strdup(command));
		else
		{
			if (errno == EACCES)
				perror(command);
			return (NULL);
		}
	}
	return (check_path(command, list));
}

void	spawn_binary(char *binary_path, t_ast_node *node, t_state *state)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return ;
	}
	else if (pid == 0)
		child_process(binary_path, node, state);
	else
		parent_process(pid, state);
}
