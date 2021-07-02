/*
** EPITECH PROJECT, 2021
** my sokoban
** File description:
** move player
*/

#include "my_sokoban.h"
#include "ncurses.h"
#include <signal.h>

static vector2i get_move(vector2i const obj, int const key)
{
    switch (key) {
    case right:
        return ((vector2i) {obj.x + 1, obj.y});
    case up:
        return ((vector2i) {obj.x, obj.y - 1});
    case left:
        return ((vector2i) {obj.x - 1, obj.y});
    case down:
        return ((vector2i) {obj.x, obj.y + 1});
    default:
        return obj;
    }
}

void display_holes(map_t *map)
{
    hole_l *tmp = map->holes;

    while (tmp) {
        if (tile(tmp->pos.x, tmp->pos.y) == ' ')
            tile(tmp->pos.x, tmp->pos.y) = 'O';
        tmp = tmp->next;
    }
}

vector2i move_obj(map_t *map, vector2i const obj, int const key)
{
    vector2i move = get_move(obj, key);
    vector2i box;

    if (MOVE_TILE == '#' || OUT_OF_MAP || same_pos(obj, move))
        return obj;
    if (MOVE_TILE == 'X') {
        if (CURENT_TILE == 'P') {
            box = move_obj(map, move, key);
            if (same_pos(move, box))
                return obj;
        }
        else
            return obj;
    }
    MOVE_TILE = CURENT_TILE;
    CURENT_TILE = ' ';
    display_holes(map);
    return move;
}