/*
** EPITECH PROJECT, 2021
** test
** File description:
** my strtok
*/

#include <criterion/criterion.h>
#include "my_lib.h"

Test(test_1, my_strtok)
{
    char *str = "1234567890";
    char *test = my_strtok(&str, '7');

    cr_assert_str_eq(test, "1234567");
}