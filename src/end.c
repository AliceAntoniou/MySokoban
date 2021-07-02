/*
** EPITECH PROJECT, 2021
** my sokoban
** File description:
** end
*/

#include "my_sokoban.h"
#include "ncurses.h"

int is_in_hole(hole_l *holes, vector2i const obj)
{
    hole_l *tmp = holes;

    while (tmp) {
        if (tmp->pos.x == obj.x && tmp->pos.y == obj.y)
            return 1;
        tmp = tmp->next;
    }
    return 0;
}

static int is_win(map_t *map)
{
    hole_l *tmp = map->holes;
    int filled = 0;

    while (tmp) {
        if (tile(tmp->pos.x, tmp->pos.y) == 'X')
            filled++;
        tmp = tmp->next;
    }
    if (filled == map->hole_nbr)
        return 1;
    return 0;
}

static int is_stuck(map_t *map, vector2i const obj)
{
    if (tile(obj.x, obj.y) != 'X' || is_in_hole(map->holes, obj))
        return 0;
    if ((tile(obj.x, obj.y + 1) == '#' || tile(obj.x, obj.y + 1) == 'X')\
        && (tile(obj.x + 1, obj.y) == '#' || tile(obj.x + 1, obj.y) == 'X'))
        return 1;
    if ((tile(obj.x, obj.y - 1) == '#' || tile(obj.x, obj.y - 1) == 'X')\
        && (tile(obj.x + 1, obj.y) == '#' || tile(obj.x + 1, obj.y) == 'X'))
        return 1;
    if ((tile(obj.x, obj.y - 1) == '#' || tile(obj.x, obj.y - 1) == 'X')\
        && (tile(obj.x - 1, obj.y) == '#' || tile(obj.x - 1, obj.y) == 'X'))
        return 1;
    if ((tile(obj.x, obj.y + 1) == '#' || tile(obj.x, obj.y + 1) == 'X')\
        && (tile(obj.x - 1, obj.y) == '#' || tile(obj.x - 1, obj.y) == 'X'))
        return 1;
    return 0;
}

int check_boxs(map_t *map)
{
    int test = 0;

    for (size_t y = 0; map->array[y]; y++)
        for (size_t x = 0; map->array[y][x]; x++) {
            if (is_stuck(map, (vector2i) {x, y}))
                test++;
        }
    if (test == map->box_nbr)
        return 0;
    return 1;
}

int is_end(map_t *map, vector2i player, int key, char const *filename)
{
    char const *args[] = {"restart", filename, NULL};
    int test = -1;

    if (player.x == -1)
        test = 1;
    if (key == 32)
        test = (sokoban(2, args));
    if (is_win(map))
        test = 0;
    if (check_boxs(map) == 0)
        test = 1;
    return test;
}