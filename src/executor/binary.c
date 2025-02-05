/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:33:45 by iasonov           #+#    #+#             */
/*   Updated: 2025/02/05 20:33:54 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

void	compose_path(char *buffer, char *dir, char *command)
{
	int		dir_len;
	char	*backslash;

	dir_len = ft_strlen(dir);
	if (dir[dir_len - 1] == '/')
		backslash = "";
	else
		backslash = "/";
	ft_str_builder(buffer, dir_len + ft_strlen(command) + 2,
		dir, backslash, command, NULL);
}

char	*check_path(char *command, t_array_list *list)
{
	char	*path;
	char	**dirs;
	int		i;
	char	*full_path;
	char	buffer[1024];

	path = array_list_get_env_value(list, "PATH");
	if (!path)
		return (NULL);
	dirs = ft_split(path, ':');
	i = 0;
	while (dirs[i])
	{
		compose_path(buffer, dirs[i], command);
		full_path = ft_strdup(buffer);
		if (access(full_path, X_OK) == 0)
		{
			free_dirs(dirs);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_dirs(dirs);
	return (NULL);
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
			return (NULL);
	}
	return (check_path(command, list));
}

void	spawn_binary(char *binary_path, t_ast_node *node, t_state *state)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return ;
	}
	else if (pid == 0)
	{
		if (execve(binary_path, node->args, state->envp_list->data) < 0)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			state->last_exit_code = WEXITSTATUS(status);
	}
}
