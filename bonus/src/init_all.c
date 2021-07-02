/*
** EPITECH PROJECT, 2021
** my graphical sokoban
** File description:
** init
*/

#include "graphic.h"
#include <stdlib.h>

sfRenderWindow *create_window(void)
{
    sfVideoMode mode = {1088, 704, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode,
                    "Runner", sfClose, NULL);
    sfVector2i mpos = {1440, 10};

    if (window == NULL)
        return NULL;
    sfRenderWindow_setPosition(window, mpos);
    sfRenderWindow_setFramerateLimit(window, 30);
    return (window);
}

sfSprite ***create_board(sfVector2i size)
{
    sfSprite ***board = malloc(sizeof(sfSprite **) * size.y + 1);
    int y;
    int x;

    for (y = 0; y < size.y; y++) {
        board[y] = malloc(sizeof(sfSprite *) * size.x + 1);
        for (x = 0; x < size.x; x++) {
            board[y][x] = sfSprite_create();
            sfSprite_setPosition(board[y][x], (sfVector2f) {64 * x, 64 * y});
        }
        board[y][x] = NULL;
    }
    board[y] = NULL;
    return board;
}

textures_t *init_texture(void)
{
    textures_t *textures = malloc(sizeof(textures_t));

    textures->box = sfTexture_createFromFile("bonus/textures/box.png", NULL);
    textures->floor = sfTexture_createFromFile("bonus/textures/floor.png", NULL);
    textures->hole = sfTexture_createFromFile("bonus/textures/hole.png", NULL);
    textures->player = sfTexture_createFromFile("bonus/textures/player.png", NULL);
    textures->wall = sfTexture_createFromFile("bonus/textures/wall.png", NULL);
    return textures;
}