/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 00:40:18 by iasonov           #+#    #+#             */
/*   Updated: 2025/02/14 21:20:05 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_builtin(t_ast_node *node, t_state *state)
{
	int	saved_stdin;
	int	saved_stdout;

	if (apply_redirections(node, &saved_stdin, &saved_stdout) < 0)
		return ;
	if (ft_strcmp(node->args[0], "pwd") == 0)
		builtin_pwd();
	else if (ft_strcmp(node->args[0], "cd") == 0)
		builtin_cd(node);
	else if (ft_strcmp(node->args[0], "exit") == 0)
		builtin_exit(state);
	else if (ft_strcmp(node->args[0], "echo") == 0)
		builtin_echo(node);
	else if (ft_strcmp(node->args[0], "env") == 0)
		builtin_env(state);
	else if (ft_strcmp(node->args[0], "export") == 0)
		builtin_export(node, state);
	else if (ft_strcmp(node->args[0], "unset") == 0)
		builtin_unset(node, state);
	restore_fds(saved_stdin, saved_stdout);
}

void	execute_binary(t_ast_node *node, t_state *state)
{
	char	*binary_path;
	int		saved_stdin;
	int		saved_stdout;

	if (apply_redirections(node, &saved_stdin, &saved_stdout) < 0)
		return ;
	binary_path = find_binary_path(node->args[0], state->envp_list);
	if (!binary_path)
	{
		ft_write(node->args[0], STDOUT_FILENO);
		ft_write(": command not found\n", STDOUT_FILENO);
		restore_fds(saved_stdin, saved_stdout);
		return ;
	}
	spawn_binary(binary_path, node, state);
	restore_fds(saved_stdin, saved_stdout);
	free(binary_path);
}

void	execute_redirection_node(t_ast_node *node, t_state *state)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (apply_redirections(node, &saved_stdin, &saved_stdout) < 0)
	{
		restore_fds(saved_stdin, saved_stdout);
		return ;
	}
	if (node->left != NULL)
		execute_ast(node->left, state);
	else
		printf("Syntax error: missing command before redirection\n");
	restore_fds(saved_stdin, saved_stdout);
}

void	execute_ast(t_ast_node *node, t_state *state)
{
	if (node == NULL)
		return ;
	if (node->type == NODE_REDIRECTION)
	{
		execute_redirection_node(node, state);
		return ;
	}
	if (node->type == NODE_COMMAND)
	{
		if (is_builtin(node))
			execute_builtin(node, state);
		else
			execute_binary(node, state);
	}
	else if (node->type == NODE_PIPE)
		execute_pipe(node, state);
	else
		printf("Unknown command type %d\n", node->type);
}
