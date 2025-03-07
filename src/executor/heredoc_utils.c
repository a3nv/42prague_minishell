/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 21:16:56 by iasonov           #+#    #+#             */
/*   Updated: 2025/02/16 21:52:52 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	process_heredoc_lines(int fd, char *delim)
{
	char	*line;

	while (1)
	{
		ft_write("heredoc> ", STDERR_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		line[strcspn(line, "\n")] = '\0';
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			cleanup();
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	cleanup();
}

int	write_heredoc(char *tmp_file, char *delim)
{
	int	fd;

	fd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("minishell");
		return (-1);
	}
	process_heredoc_lines(fd, delim);
	close(fd);
	return (0);
}

int	handle_heredoc(t_ast_node *node)
{
	int		fd;
	char	*tmp_file;

	tmp_file = "/tmp/minishell_heredoc";
	if (node->redirection.heredoc_delim == NULL)
		return (0);
	if (write_heredoc(tmp_file, node->redirection.heredoc_delim) < 0)
		return (-1);
	fd = open(tmp_file, O_RDONLY);
	if (fd < 0)
	{
		perror("minishell");
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}
