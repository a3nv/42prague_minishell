/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_array_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:00:19 by iasonov           #+#    #+#             */
/*   Updated: 2025/01/05 21:04:44 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <criterion/criterion.h>
#include <criterion/logging.h>

Test(array_list, new_list) {
	t_array_list *list = array_list_create(1);
	array_list_add(list, "test=test");
	cr_assert_not_null(list, "Lish should not be null");
	cr_assert_str_eq(list->data[0], "test=test", "Expected 'test=test' but got '%s'", list->data[0]);
	cr_assert_eq(list->size, 1);
	array_list_free(list);
}

Test(array_list, updated_list) {
	t_array_list *list = array_list_create(1);
	array_list_add(list, "test=test");
	cr_assert_not_null(list, "Lish should not be null");
	cr_assert_str_eq(list->data[0], "test=test", "Expected 'test=test' but got '%s'", list->data[0]);
	cr_assert_eq(list->size, 1);
	array_list_add(list, "test2=test2");
	cr_assert_str_eq(list->data[0], "test=test", "Expected 'test=test' but got '%s'", list->data[0]);
	cr_assert_str_eq(list->data[1], "test2=test2", "Expected 'test2=test2' but got '%s'", list->data[0]);
	cr_assert_eq(list->size, 2);
	array_list_free(list);
}

Test(array_list, remove_from_list) {
	t_array_list *list = array_list_create(2);
	array_list_add(list, "test=test");
	array_list_add(list, "test2=test2");
	array_list_remove(list, "test");
	cr_assert_str_eq(list->data[0], "test2=test2", "Expected 'test2=test2' but got '%s'", list->data[0]);
	cr_assert_eq(list->size, 1);
	array_list_free(list);
}

Test(array_list, remove_multiple_from_list) {
	t_array_list *list = array_list_create(4);
	array_list_add(list, "test=test");
	array_list_add(list, "test22=test22");
	array_list_add(list, "test2=test2");
	array_list_add(list, "test234=test234");
	array_list_remove(list, "test2");
	cr_assert_str_eq(list->data[0], "test=test", "Expected 'test=test' but got '%s'", list->data[0]);
	cr_assert_str_eq(list->data[1], "test22=test22", "Expected 'test22=test22' but got '%s'", list->data[0]);
	cr_assert_str_eq(list->data[2], "test234=test234", "Expected 'test234=test234' but got '%s'", list->data[0]);
	cr_assert_eq(list->size, 3);
	array_list_remove(list, "test234");
	cr_assert_str_eq(list->data[0], "test=test", "Expected 'test=test' but got '%s'", list->data[0]);
	cr_assert_str_eq(list->data[1], "test22=test22", "Expected 'test22=test22' but got '%s'", list->data[0]);
	cr_assert_eq(list->size, 2);
	array_list_free(list);
}
