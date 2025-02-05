/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 19:58:23 by iasonov           #+#    #+#             */
/*   Updated: 2025/02/05 21:17:49 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h" 

int	set_input_redirection(char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd < 0)
	{
		perror("minishell");
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	set_output_redirection(char *outfile, int append)
{
	int	fd;
	int	flags;

	if (append == 1)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(outfile, flags, 0644);
	if (fd < 0)
	{
		perror("minishell");
		return (-1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	handle_redirections(t_ast_node *node)
{
	int	ret;

	ret = 0;
	if (node->redirection.infile != NULL)
	{
		ret = set_input_redirection(node->redirection.infile);
		if (ret < 0)
			return (-1);
	}
	if (node->redirection.outfile != NULL)
	{
		ret = set_output_redirection(node->redirection.outfile,
				node->redirection.append);
		if (ret < 0)
			return (-1);
	}
	return (0);
}

/*
 * Helper function that saves STDIN and STDOUT,
 * then applies heredoc and redirections.
 * On error, it restores the fds and returns -1.
 */
int	apply_redirections(t_ast_node *node, int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
	if (handle_heredoc(node) < 0 || handle_redirections(node) < 0)
	{
		dup2(*saved_stdin, STDIN_FILENO);
		dup2(*saved_stdout, STDOUT_FILENO);
		close(*saved_stdin);
		close(*saved_stdout);
		return (-1);
	}
	return (0);
}

/*
 * Helper function to restore STDIN and STDOUT
 * from the saved file descriptors.
 */
void	restore_fds(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}
