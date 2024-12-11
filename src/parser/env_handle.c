#include "../includes/minishell.h"

int	is_env_var_set(const char *var)
{
	if (getenv(var))
		return (1);
	return (0);
}

int	export_env_var(const char *var)
{
	char	*eq_pos;
	char	*key;
	char	*value;

	eq_pos = ft_strchr(var, '=');
	if (eq_pos)
	{
		key = ft_substr(var, 0, eq_pos - var);
		value = ft_strdup(eq_pos + 1);
		if (setenv(key, value, 1) == -1)
		{
			perror("setenv failed");
			free(key);
			free(value);
			return (1);
		}
		free(key);
		free(value);
		return (0);
	}
	return (1);
}

int	unset_env_var(const char *var)
{
	if (unsetenv(var) == -1)
	{
		perror("unsetenv failed");
		return (1);
	}
	return (0);
}

int	handle_env_variables(char *input)
{
	if (ft_strncmp(input, "export ", 7) == 0)
	{
		return (export_env_var(input + 7));
	}
	if (ft_strncmp(input, "unset ", 6) == 0)
	{
		return (unset_env_var(input + 6));
	}
	return (0);
}

char	*replace_env_var(const char *input)
{
	char	*result;
	char	*var_name;
	char	*env_value;
	int		i;
	int		j;
	int		result_len;

	result = NULL;
	var_name = NULL;
	env_value = NULL;
	i = 0;
	j = 0;
	result_len = 0;
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1] != '\0')
		{
			i++;
			j = 0;
			while (input[i + j] && (ft_isalnum(input[i + j]) || input[i
					+ j] == '_'))
				j++;
			var_name = ft_substr(input, i, j);
			env_value = getenv(var_name);
			if (env_value)
			{
				result_len += ft_strlen(env_value);
				result = ft_strjoin(result, env_value);
			}
			i += j;
			free(var_name);
		}
		else
		{
			result_len++;
			result = ft_strjoin_char(result, input[i]);
			i++;
		}
	}
	return (result);
}

// to do
// need to implement somewhere replace_env_var(input) but almost all i tried flawlessly failed
// should be in lexer as i think
// also tried make usage in main but it works weird in windows
// bloody hell :D