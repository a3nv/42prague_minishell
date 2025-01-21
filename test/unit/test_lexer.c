#include <criterion/criterion.h>
#include <criterion/logging.h>
#include "../../includes/minishell.h"

Test(lexer, simple_command) {
	t_list *list;

	cr_log_info("Test: Simple command\n");
	list = lexer("ls -l");
	cr_assert_not_null(list, "List should not be NULL");
	cr_assert_eq(ft_lstsize(list), 2, "Expected list size: 2, but got %d", ft_lstsize(list));
	cr_assert_str_eq(((t_token *)list->content)->value, "ls", "Expected first token to be 'ls', but got '%s'", ((t_token *)list->content)->value);
	cr_assert_str_eq(((t_token *)list->next->content)->value, "-l", "Expected second token to be '-l', but got '%s'", ((t_token *)list->next->content)->value);
	ft_lstclear(&list, free_list);
}

Test(lexer, empty_command) {
	t_list *list;
	char *str = NULL;

	cr_log_info("Test: NULL input\n");
	list = lexer(str);
	cr_assert_null(list, "List should be NULL");
}

Test(lexer, blank_command) {
	t_list *list;

	cr_log_info("Test: Blank input\n");
	list = lexer("                  			 \t \n ");
	cr_assert_null(list, "List should be NULL");
}

Test(lexer, multiple_spaces) {
	t_list *list;

	cr_log_info("Test: Command with multiple spaces\n");
	list = lexer("ls     -l");
	cr_assert_not_null(list, "List should not be NULL");
	cr_assert_eq(ft_lstsize(list), 2, "Expected list size: 2, but got %d", ft_lstsize(list));
	cr_assert_str_eq(((t_token *)list->content)->value, "ls", "Expected first token to be 'ls', but got '%s'", ((t_token *)list->content)->value);
	cr_assert_str_eq(((t_token *)list->next->content)->value, "-l", "Expected second token to be '-l', but got '%s'", ((t_token *)list->next->content)->value);
	ft_lstclear(&list, free_list);
}

Test(lexer, special_characters) {
	t_list *list;

	cr_log_info("Test: Command with special characters\n");
	list = lexer("ls | grep foo");
	cr_assert_not_null(list, "List should not be NULL");
	cr_assert_eq(ft_lstsize(list), 4, "Expected list size: 4, but got %d", ft_lstsize(list));
	cr_assert_str_eq(((t_token *)list->content)->value, "ls", "Expected first token to be 'ls', but got '%s'", ((t_token *)list->content)->value);
	cr_assert_str_eq(((t_token *)list->next->content)->value, "|", "Expected second token to be '|', but got '%s'", ((t_token *)list->next->content)->value);
	cr_assert_str_eq(((t_token *)list->next->next->content)->value, "grep", "Expected third token to be 'grep', but got '%s'", ((t_token *)list->next->next->content)->value);
	cr_assert_str_eq(((t_token *)list->next->next->next->content)->value, "foo", "Expected fourth token to be 'foo', but got '%s'", ((t_token *)list->next->next->next->content)->value);
	ft_lstclear(&list, free_list);
}

Test(lexer, quoted_string) {
	t_list *list;

	cr_log_info("Test: Command with quoted input\n");
	list = lexer("echo \"hello world\"");
	cr_assert_not_null(list, "List should not be NULL");
	cr_assert_eq(ft_lstsize(list), 2, "Expected list size: 2, but got %d", ft_lstsize(list));
	cr_assert_str_eq(((t_token *)list->content)->value, "echo", "Expected first token to be 'echo', but got '%s'", ((t_token *)list->content)->value);
	cr_assert_str_eq(((t_token *)list->next->content)->value, "hello world", "Expected second token to be 'hello wortld', but got '%s'", ((t_token *)list->next->content)->value);
	ft_lstclear(&list, free_list);

}

Test(lexer, single_quoted_string) {
	t_list *list;

	cr_log_info("Test: Command with single quoted input\n");
	list = lexer("echo 'hello world'");
	cr_assert_not_null(list, "List should not be NULL");
	cr_assert_eq(ft_lstsize(list), 2, "Expected list size: 2, but got %d", ft_lstsize(list));
	cr_assert_str_eq(((t_token *)list->content)->value, "echo", "Expected first token to be 'echo', but got '%s'", ((t_token *)list->content)->value);
	cr_assert_str_eq(((t_token *)list->next->content)->value, "hello world", "Expected second token to be 'hello wortld', but got '%s'", ((t_token *)list->next->content)->value);

	ft_lstclear(&list, free_list);

}
