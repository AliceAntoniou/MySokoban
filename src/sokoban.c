/*
** EPITECH PROJECT, 2021
** my sokoban
** File description:
** sokoban
*/

#include <stdio.h>
#include "my_lib.h"
#include "my_sokoban.h"
#include <stdlib.h>

void add_nod(hole_l **head, vector2i pos)
{
    hole_l *node = malloc(sizeof(hole_l));

    if (*head == NULL) {
        node->pos = pos;
        node->next = NULL;
        (*head) = node;
        return;
    }
    node->pos = pos;
    node->next = (*head);
    (*head) = node;
    return;
}

void print_usage(void)
{
    my_putstr("USAGE\n");
    my_putstr("     ./my_sokoban map\n");
    my_putstr("DESCRIPTION\n");
    my_putstr("     map  file representing the warehouse map, \
                                containing '#' for walls,\n");
    my_putstr("          'P' for the player, 'X' for boxes and \
                                'O' for storage locations.\n");
}

void free_map(map_t *map)
{
    hole_l *tmp = map->holes;

    while (map->holes) {
        tmp = map->holes->next;
        free(map->holes);
        map->holes = tmp;
    }
    for (size_t i = 0; map->array[i]; i++)
        free(map->array[i]);
    free(map->array);
}

int sokoban(int ac, char const *av[])
{
    map_t map;
    int value = 0;

    if (ac != 2)
        return 84;
    if (my_str_is_identical(av[1], "-h")) {
        print_usage();
        return 0;
    }
    get_map(&map, av[1]);
    if (!map.array)
        return 84;
    value = game(&map, av[1]);
    free_map(&map);
    if (value == -1)
        return 0;
    return value;
}