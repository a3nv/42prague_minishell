/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aevstign <aevstign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:12:25 by aevstign          #+#    #+#             */
/*   Updated: 2025/02/05 21:21:12 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <signal.h>
# include <stddef.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>
# include <fcntl.h>
# include "../libft/libft.h"

# define MAX_TOKENS 100
# ifndef DEBUG_MODE
#  define DEBUG_MODE 0
# endif

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_INPUT,
	TOKEN_OUTPUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_SINGLE_QUOTE,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_WHITESPACE,
	TOKEN_EOF,
	TOKEN_ERROR,
	TOKEN_NULL,
	TOKEN_UNKNOWN,
}			t_token_type;

typedef struct s_token
{
	t_token_type	type;
	int				counter;
	char			*value;
	int				expandable;
}				t_token;

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIRECTION,
}				t_node_type;

/*
 * inflie - '<'
 * outfile - '>' and '>>'
 * append - 1 for '>>' and 0 for '>'
 * heredoc '<<'
 */
typedef struct s_redirection
{
	char			*infile;
	char			*outfile;
	int				append;
	char			*heredoc_delim;
}				t_redirection;

typedef struct s_ast_node
{
	t_node_type			type;
	char				**args;
	int					argc;
	int					file_type;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	t_redirection		redirection;
}				t_ast_node;

typedef struct s_state
{
	char			*input;
	t_list			*token_list;
	t_ast_node		*root_node;
	t_ast_node		*current_node;
	t_array_list	*envp_list;
	int				last_exit_code;
}			t_state;

// alloc_utils
t_state			*init(char **envp);

// gc
void			free_list(void *content);
void			reset_state(t_state *state);

// main utils
void			print_tokens(t_list *lexer);
const char		*get_token_type_name(t_token_type type);

// printer
void			print_node(t_ast_node *node, int depth);
void			display_ast(t_ast_node *node, int depth);

// lexer_utils
t_token_type	get_operator_type(char *str, int *advanced);
t_token_type	get_char_type(char c);
t_token			*create_token(void);
void			free_token(t_token *token);
char			*strip_quotes(char *str);

// lexer
t_list			*lexer(char *input);

// parser
t_ast_node		*parse_tokens(t_state *state);
void			create_command_node(t_ast_node **current_node,
					t_list *list_item, t_token *token, t_state *state);

// parseer node utils 
t_ast_node		*create_ast_node(t_node_type type, char *value, t_list *list);

// parser utils
int				is_redirect(t_token_type type);
int				count_args(t_list *current);
void			free_args(char **args);
int				validate_input(char *input);
char			*expand_variable(t_state *state, char *value);

// env expander
char			*expand_variable(t_state *state, char *value);

// parser
void			execute_ast(t_ast_node *node, t_state *state);

// executor
void			builtin_pwd(void);
void			builtin_cd(t_ast_node *node);
void			builtin_exit(t_state *state);
void			builtin_echo(t_ast_node *node);
void			builtin_env(t_state *state);
void			builtin_export(t_ast_node *node, t_state *state);
void			builtin_unset(t_ast_node *node, t_state *state);
void			builtin_grep(t_ast_node *node);
void			builtin_wc(void);
void			execute_pipe(t_ast_node *node, t_state *state);

int				handle_redirections(t_ast_node *node);
int				handle_heredoc(t_ast_node *node);

// builtin_export_utils
int				count_env_vars(char	**envp);
void			clear_copy(char **copy);
char			**copy_envp(char **original);

// env utils
t_pair			*parse_arg(char *arg);

// signals
void			register_signals(void);

// executor_utils
int				is_builtin(t_ast_node *node);

// binary utils
void			free_dirs(char **dirs);

// binary
char			*check_path(char *command, t_array_list *list);
void			execute_binary(t_ast_node *node, t_state *state);
char			*find_binary_path(char *command, t_array_list *list);
void			spawn_binary(char *binary_path, t_ast_node *node,
					t_state *state);

// redirection utils && heredoc utils
int				write_heredoc(char *tmp_file, char *delim);
int				handle_heredoc(t_ast_node *node);
int				handle_redirections(t_ast_node *node);
int				apply_redirections(t_ast_node *node, int *saved_stdin,
					int *saved_stdout);
void			restore_fds(int saved_stdin, int saved_stdout);

// envp utils
void			free_envp(t_state *state);
void			copy_from_list(char **nenvp, t_hashmap_entry *entry, size_t *i);
char			**generate_envp_from_map(t_hashmap *map);
void			update_envp(t_state *state);
char			*array_list_get(t_array_list *list, char *key);
char			*array_list_get_env_value(t_array_list *list, char *key);

#endif
