/*
** EPITECH PROJECT, 2021
** my graphical sokoban
** File description:
** end
*/

#include "graphic.h"

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

int is_end(map_t *map, vector2i player, sfRenderWindow *window, char const *filename)
{
    char const *args[] = {"restart", filename, NULL};

    if (player.x == -1)
        return 1;
    if (sfKeyboard_isKeyPressed(sfKeySpace)) {
        sfRenderWindow_close(window);
        return (sokoban(2, args));
    }
    if (sfKeyboard_isKeyPressed(sfKeyEscape)) {
        sfRenderWindow_close(window);
        return 0;
    }
    if (is_win(map))
        return 0;
    return -1;
}