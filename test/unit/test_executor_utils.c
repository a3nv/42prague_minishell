#include <criterion/criterion.h>
#include <criterion/logging.h>
#include "../../includes/minishell.h"

Test(is_builtin, valid_builtin_commands) {
    t_ast_node node = { .type = NODE_COMMAND, .args = (char *[]){"cd", NULL} };

    cr_log_info("Test: 'cd' should be a builtin\n");
    cr_assert_eq(is_builtin(&node), 1, "'cd' should return 1 but returned 0");

    node.args[0] = "echo";
    cr_log_info("Test: 'echo' should be a builtin\n");
    cr_assert_eq(is_builtin(&node), 1, "'echo' should return 1 but returned 0");

    node.args[0] = "unset";
    cr_log_info("Test: 'unset' should be a builtin\n");
    cr_assert_eq(is_builtin(&node), 1, "'unset' should return 1 but returned 0");
}

Test(is_builtin, invalid_commands) {
    t_ast_node node = { .type = NODE_COMMAND, .args = (char *[]){"invalid", NULL} };

    cr_log_info("Test: 'invalid' should not be a builtin\n");
    cr_assert_eq(is_builtin(&node), 0, "'invalid' should return 0 but returned 1");

    node.args[0] = "ls";
    cr_log_info("Test: 'ls' should not be a builtin\n");
    cr_assert_eq(is_builtin(&node), 0, "'ls' should return 0 but returned 1");
}

Test(is_builtin, non_command_node) {
    t_ast_node node = { .type = NODE_PIPE, .args = (char *[]){"cd", NULL} };

    cr_log_info("Test: Non-command node should not be a builtin\n");
    cr_assert_eq(is_builtin(&node), 0, "Non-command node should return 0 but returned 1");
}

Test(is_builtin, null_args) {
    t_ast_node node = { .type = NODE_COMMAND, .args = NULL };

    cr_log_info("Test: Null args should not be a builtin\n");
    cr_assert_eq(is_builtin(&node), 0, "Node with null args should return 0 but returned 1");
}

Test(is_builtin, null_node) {
    cr_log_info("Test: Null node should not be a builtin\n");
    cr_assert_eq(is_builtin(NULL), 0, "Null node should return 0 but returned 1");
}

