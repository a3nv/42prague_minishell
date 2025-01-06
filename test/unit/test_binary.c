/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_binary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 19:20:13 by iasonov           #+#    #+#             */
/*   Updated: 2025/01/05 21:54:10 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <criterion/criterion.h>
#include <criterion/logging.h>

Test(check_path, command_exists_in_path) {
    t_array_list *list = array_list_create(1);
    array_list_add(list, "PATH=/bin:/usr/bin");
    char *result = check_path("ls", list);
    cr_assert_not_null(result, "Expected a valid path but got NULL");
    cr_assert_str_eq(result, "/bin/ls", "Expected '/bin/ls' but got '%s'", result);
    free(result);
    array_list_free(list);
}

Test(check_path, command_does_not_exist_in_path) {
    t_array_list *list = array_list_create(1);
    array_list_add(list, "PATH=/bin:/usr/bin");
    char *result = check_path("nonexistentcommand", list);
    cr_assert_null(result, "Expected NULL but got '%s'", result);
    array_list_free(list);
}

Test(check_path, path_variable_missing) {
    t_array_list *list = array_list_create(1);
    char *result = check_path("ls", list);
    cr_assert_null(result, "Expected NULL but got '%s'", result);
    array_list_free(list);
}

Test(check_path, path_variable_empty) {
    t_array_list *list = array_list_create(1);
    array_list_add(list, "");
    char *result = check_path("ls", list);
    cr_assert_null(result, "Expected NULL but got '%s'", result);
    array_list_free(list);
}

Test(check_path, path_with_empty_entries) {
    t_array_list *list = array_list_create(1);
    array_list_add(list, "PATH=/bin::/usr/bin");
    char *result = check_path("ls", list);
    cr_assert_not_null(result, "Expected a valid path but got NULL");
    cr_assert_str_eq(result, "/bin/ls", "Expected '/bin/ls' but got '%s'", result);
    free(result);
    array_list_free(list);
}

Test(check_path, path_with_trailing_slashes) {
    t_array_list *list = array_list_create(1);
    array_list_add(list, "PATH=/bin/:/usr/bin/");
    char *result = check_path("ls", list);
    cr_assert_not_null(result, "Expected a valid path but got NULL");
    cr_assert_str_eq(result, "/bin/ls", "Expected '/bin/ls' but got '%s'", result);
    free(result);
    array_list_free(list);
}

Test(check_path, non_executable_file) {
    t_array_list *list = array_list_create(1);
    array_list_add(list, "PATH=/tmp");
    char *filepath = "/tmp/testfile";
    FILE *file = fopen(filepath, "w");
    fprintf(file, "Test content");
    fclose(file);
    char *result = check_path("testfile", list);
    cr_assert_null(result, "Expected NULL for non-executable file but got '%s'", result);
    remove(filepath);
    array_list_free(list);
}

Test(check_path, command_exists_in_last_path_entry) {
    t_array_list *list = array_list_create(1);
    array_list_add(list, "PATH=/nonexistent:/bin");
    char *result = check_path("ls", list);
    cr_assert_not_null(result, "Expected a valid path but got NULL");
    cr_assert_str_eq(result, "/bin/ls", "Expected '/bin/ls' but got '%s'", result);
    free(result);
    array_list_free(list);
}

