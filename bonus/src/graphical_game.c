/*
** EPITECH PROJECT, 2021
** my graphical sokoban
** File description:
** game
*/

#include "graphic.h"
#include <unistd.h>

int display(sfRenderWindow *window, sfSprite ***board, map_t const *map, textures_t *textures)
{
    sfRenderWindow_clear(window, sfBlack);
    for (size_t y = 0; map->array[y] != NULL; y++) {
        for (size_t x = 0; map->array[y][x] != '\n' && map->array[y][x] != '\0'; x++) {
            switch (map->array[y][x]) {
            case 'X':
                sfSprite_setTexture(board[y][x], textures->box, 0);
                break;
            case ' ':
                sfSprite_setTexture(board[y][x], textures->floor, 0);
                break;
            case 'O':
                sfSprite_setTexture(board[y][x], textures->hole, 0);
                break;
            case 'P':
                sfSprite_setTexture(board[y][x], textures->player, 0);
                break;
            case '#':
                sfSprite_setTexture(board[y][x], textures->wall, 0);
            }
            sfRenderWindow_drawSprite(window, board[y][x], NULL);
        }   
    }
    sfRenderWindow_display(window);
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

static int get_key(void)
{
    if (sfKeyboard_isKeyPressed(sfKeyLeft))
        return left;
    if (sfKeyboard_isKeyPressed(sfKeyRight))
        return right;
    if (sfKeyboard_isKeyPressed(sfKeyUp))
        return up;
    if (sfKeyboard_isKeyPressed(sfKeyDown))
        return down;
    return 0;
}

void center_the_map(sfSprite ***board, vector2i player, map_t *map)
{
    sfVector2f pos = sfSprite_getPosition(**board);
    sfVector2f move = {0, 0};

    player.x = player.x * 64 + pos.x;
    player.y = player.y * 64 + pos.y;
    while (0 < player.x - 512 + move.x && pos.x + move.x + (64 * map->x) >= 1152)
        move.x -= 64;
    while (512 > player.x + move.x && pos.x + move.x <= -64)
        move.x += 64;
    while (0 < player.y - 320 + move.y && pos.y + move.y + (64 * map->y) >= 768)
        move.y -= 64;
    while (320 > player.y + move.y && pos.y + move.y <= -64)
        move.y += 64;
    if (move.x == 0 && move.y == 0)
        return;
    for (size_t y = 0; board[y]; y++)
        for (size_t x = 0; board[y][x]; x++)
            sfSprite_move(board[y][x], move);
}

int game(map_t *map, char const *filename)
{
    sfRenderWindow *window = create_window();
    sfSprite ***board = create_board((sfVector2i) {map->x, map->y});
    vector2i player = get_player_pos(map);
    textures_t *textures = init_texture();
    int key = 0;
    int end = -1;

    if (player.x == -1)
        return 84;
    usleep(200000);
    while (sfRenderWindow_isOpen(window) && !INTERUPT && end == -1) {
        player = move_obj(map, player, key);
        end = is_end(map, player, window, filename);
        center_the_map(board, player, map);
        if (end > -1) {
            display(window, board, map, textures);
            if (sfRenderWindow_isOpen(window))
                usleep(700000);
            sfRenderWindow_close(window);
        }
        if (!display(window, board, map, textures)) {
            end = 84;
            sfRenderWindow_close(window);
        }
        usleep(200000);
        key = get_key();
    }
    sfRenderWindow_close(window);
    return end;
}