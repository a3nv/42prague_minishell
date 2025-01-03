/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_envp_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 21:14:05 by iasonov           #+#    #+#             */
/*   Updated: 2025/01/03 21:28:03 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <stdio.h>
#include "../../includes/minishell.h"

Test(generate_envp_from_map, basic_functionality) {
    t_hashmap *map = ft_hashmap_create(3);
    ft_hashmap_insert(map, "USER", "testuser");
    ft_hashmap_insert(map, "SHELL", "/bin/bash");
    ft_hashmap_insert(map, "HOME", "/home/testuser");
    char **envp = generate_envp_from_map(map);
    cr_assert_not_null(envp, "Generated envp should not be NULL");
    const char *expected_entries[] = {
        "USER=testuser",
        "SHELL=/bin/bash",
        "HOME=/home/testuser",
        NULL
    };
    for (int i = 0; expected_entries[i] != NULL; i++) {
        bool found = false;
        for (int j = 0; envp[j] != NULL; j++) {
            if (strcmp(expected_entries[i], envp[j]) == 0) {
                found = true;
                break;
            }
        }
        cr_assert(found, "Expected entry '%s' not found in envp", expected_entries[i]);
    }
    cr_assert_null(envp[3], "Last element of envp should be NULL");
    free_envp(&(t_state){ .envp = envp });
    ft_hashmap_free(map);
}

Test(generate_envp_from_map, empty_map) {
    t_hashmap *map = ft_hashmap_create(1);
    char **envp = generate_envp_from_map(map);
    cr_assert_not_null(envp, "Generated envp should not be NULL");
    cr_assert_null(envp[0], "First element of envp should be NULL for an empty map");
    free_envp(&(t_state){ .envp = envp });
    ft_hashmap_free(map);
}

//Test(generate_envp_from_map, duplicate_keys) {
//    t_hashmap *map = ft_hashmap_create(10);
//    ft_hashmap_insert(map, "PATH", "/usr/bin");
//    ft_hashmap_insert(map, "PATH", "/bin");
//    char **envp = generate_envp_from_map(map);
//    cr_assert_not_null(envp, "Generated envp should not be NULL");
//    cr_assert_str_eq(envp[0], "PATH=/bin", "Expected 'PATH=/bin' but got '%s'", envp[0]);
//    cr_assert_null(envp[1], "Last element of envp should be NULL");
//    free_envp(&(t_state){ .envp = envp });
//    ft_hashmap_free(map);
//}

//Test(generate_envp_from_map, special_characters) {
//    t_hashmap *map = ft_hashmap_create(10);
//    ft_hashmap_insert(map, "LANG", "en_US.UTF-8");
//    ft_hashmap_insert(map, "KEY", "value@123!");
//    char **envp = generate_envp_from_map(map);
//    cr_assert_not_null(envp, "Generated envp should not be NULL");
//    cr_assert_str_eq(envp[0], "LANG=en_US.UTF-8", "Expected 'LANG=en_US.UTF-8' but got '%s'", envp[0]);
//    cr_assert_str_eq(envp[1], "KEY=value@123!", "Expected 'KEY=value@123!' but got '%s'", envp[1]);
//    cr_assert_null(envp[2], "Last element of envp should be NULL");
//    free_envp(&(t_state){ .envp = envp });
//    ft_hashmap_free(map);
//}

//Test(generate_envp_from_map, large_number_of_entries) {
//    t_hashmap *map = ft_hashmap_create(1000);
//    for (int i = 0; i < 1000; i++) {
//        char key[16], value[16];
//        snprintf(key, sizeof(key), "KEY%d", i);
//        snprintf(value, sizeof(value), "VALUE%d", i);
//        ft_hashmap_insert(map, key, value);
//    }
//    char **envp = generate_envp_from_map(map);
//    cr_assert_not_null(envp, "Generated envp should not be NULL");
//    for (int i = 0; i < 1000; i++) {
//        char expected[32];
//        snprintf(expected, sizeof(expected), "KEY%d=VALUE%d", i, i);
//        cr_assert_str_eq(envp[i], expected, "Expected '%s' but got '%s'", expected, envp[i]);
//    }
//    cr_assert_null(envp[1000], "Last element of envp should be NULL");
//    free_envp(&(t_state){ .envp = envp });
//    ft_hashmap_free(map);
//}
