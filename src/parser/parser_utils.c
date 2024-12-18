/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 00:30:05 by aevstign          #+#    #+#             */
/*   Updated: 2024/12/18 15:28:16 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redirect(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_APPEND || type == TOKEN_REDIR_HEREDOC);
}

int	count_args(t_list *current)
{
	int		counter;
	t_token	*content;

	counter = 0;
	if (!current)
		return (counter);
	while (current)
	{
		content = current->content;
		if (content->type != TOKEN_WORD)
			break ;
		counter++;
		current = current->next;
	}
	return (counter);
}

void	fill_args(t_ast_node *command_node, t_list *list, int argc)
{
	int		i;
	t_list	*current;
	t_token	*content;

	i = 0;
	current = list;
	while (i < argc)
	{
		content = current->content;
		command_node->args[i] = ft_strdup(content->value);
		if (!command_node->args[i])
		{
			while (i > 0)
			{
				free(command_node->args[i--]);
			}
			return ;
		}
		current = current->next;
		free(content->value);
		free(content);
		i++;
	}
	command_node->args[argc] = NULL;
}

void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}
