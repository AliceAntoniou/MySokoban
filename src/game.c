/*
** EPITECH PROJECT, 2021
** my sokoban
** File description:
** game
*/

#include "my_sokoban.h"
#include "ncurses.h"

int display(WINDOW const *window, map_t const *map)
{
    int x = getmaxx(window);
    int y = getmaxy(window);

    if (x < (int) map->x || y < (int) map->y)
        return 0;
    clear();
    for (size_t i = 0; map->array[i] != NULL; i++)
        mvprintw((y - map->y) / 2 + i, (x - map->x) / 2, "%s", map->array[i]);
    refresh();
    return 1;
}

vector2i get_player_pos(map_t const *map)
{
    vector2i pos;

    for (pos.y = 0; pos.y < (int) map->y; pos.y++)
        for (pos.x = 0; pos.x < (int) map->x; pos.x++)
            if (map->array[pos.y][pos.x] == 'P')
                return pos;
    pos.x = -1;
    return pos;
}

void test_window(WINDOW *window, map_t *map)
{
    while (!display(window, map)) {
        clear();
        printw("Resize your window please");
        refresh();
        usleep(10000);
    }
}

int game(map_t *map, char const *filename)
{
    WINDOW *window = initscr();
    vector2i player = get_player_pos(map);
    int key = 0;
    int end = 0;

    if (player.x == -1)
        return 84;
    while (!INTERUPT) {
        player = move_obj(map, player, key);
        end = is_end(map, player, key, filename);
        if (end > -1)
            break;
        test_window(window, map);
        key = getch();
    }
    if (end == 0)
        display(window, map);
    usleep(1000000);
    endwin();
    return end;
}