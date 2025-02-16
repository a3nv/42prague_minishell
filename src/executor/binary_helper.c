/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 13:59:46 by iasonov           #+#    #+#             */
/*   Updated: 2025/02/16 14:09:19 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child_process(char *binary_path, t_ast_node *node, t_state *state)
{
	signal(SIGQUIT, SIG_DFL);
	if (execve(binary_path, node->args, state->envp_list->data) < 0)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	parent_process(pid_t pid, t_state *state)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		state->last_exit_code = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		state->last_exit_code = 128 + WTERMSIG(status);
}

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

/*
 * build_candidate_path:
 *   Uses compose_path to fill a buffer with the full path,
 *   then duplicates the buffer into a heap-allocated string.
 */
char	*build_candidate_path(char *dir, char *command)
{
	char	buffer[1024];
	char	*full_path;

	compose_path(buffer, dir, command);
	full_path = ft_strdup(buffer);
	return (full_path);
}

/*
 * find_accessible_path:
 *   Iterates through the array of directory strings,
 *   builds the candidate path for each directory,
 *   and checks if the executable exists and is accessible.
 *   Returns the allocated path string on success, or NULL if not found.
 */
char	*find_accessible_path(char *command, char **dirs)
{
	char	*full_path;
	int		i;

	i = 0;
	while (dirs[i])
	{
		full_path = build_candidate_path(dirs[i], command);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}
