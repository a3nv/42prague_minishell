/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 13:08:13 by iasonov           #+#    #+#             */
/*   Updated: 2024/12/31 13:36:58 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execite_pipe_child(int	*pipe_fd, t_ast_node *node,
		t_state *state, int isLeft)
{
	int	redirect_fd;
	int	pipe_read_end;
	int	pipe_write_end;

	if (isLeft)
	{
		redirect_fd = STDOUT_FILENO;
		pipe_read_end = 0;
		pipe_write_end = 1;
	}
	else
	{
		redirect_fd = STDIN_FILENO;
		pipe_read_end = 1;
		pipe_write_end = 0;
	}
	close(pipe_fd[pipe_read_end]);
	if (dup2(pipe_fd[pipe_write_end], redirect_fd) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[pipe_write_end]);
	execute_ast(node, state);
	exit(EXIT_SUCCESS);
}

void	exit_with_error(char *reason)
{
	perror(reason);
	exit(EXIT_FAILURE);
}

void	execute_pipe(t_ast_node *node, t_state *state)
{
	int		pipe_fd[2];
	pid_t	pid_left;
	pid_t	pid_right;

	if (pipe(pipe_fd) == -1)
		exit_with_error("pipe");
	pid_left = fork();
	if (pid_left == -1)
		exit_with_error("fork");
	if (pid_left == 0)
		execite_pipe_child(pipe_fd, node->left, state, 1);
	pid_right = fork();
	if (pid_right == -1)
		exit_with_error("fork");
	if (pid_right == 0)
		execite_pipe_child(pipe_fd, node->right, state, 0);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, NULL, 0);
}
