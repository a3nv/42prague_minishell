#include "../includes/minishell.h"

int	check_unclosed_quotes(const char *input)
{
	int	single_quote_count;
	int	double_quote_count;

	single_quote_count = 0;
	double_quote_count = 0;
	while (*input)
	{
		if (*input == '\'')
		{
			single_quote_count++;
		}
		else if (*input == '"')
		{
			double_quote_count++;
		}
		input++;
	}
	if (single_quote_count % 2 != 0)
	{
		ft_putstr_fd("Unclosed single quote\n", STDERR_FILENO);
		return (1);
	}
	if (double_quote_count % 2 != 0)
	{
		ft_putstr_fd("Unclosed double quote\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	check_invalid_special_characters(const char *input)
{
	while (*input)
	{
		if (*input == ';')
		{
			ft_putstr_fd("Semicolon not allowed\n", STDERR_FILENO);
			return (1);
		}
		input++;
	}
	return (0);
}

int	handle_redirection(char *input)
{
	if (ft_strnstr(input, "<<",2))
	{
		// todo heredoc
		return (1);
	}
	if (ft_strchr(input, '>') || ft_strchr(input, '<'))
	{
		// todo redirection
		return (1);
	}
	return (0);
}

int	handle_pipes(char *input)
{
	if (ft_strchr(input, '|'))
	{
		// todo pipe
		return (1);
	}
	return (0);
}

int	validate_input(char *input)
{
	if (!input)
		return (1);

	if (check_unclosed_quotes(input))
		return (1);

	if (check_invalid_special_characters(input))
		return (1);

	if (handle_redirection(input))
	{
		free(input);
		return (1);
	}

	if (handle_pipes(input))
	{
		free(input);
		return (1);
	}
	free(input);
	return (0);
}
