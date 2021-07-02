/*
** EPITECH PROJECT, 2021
** graphical sokoban
** File description:
** graphic
*/

#ifndef GRAPHICAL_SOKOBAN
#define GRAPHICAL_SOKOBAN

#include <SFML/Graphics.h>
#include <SFML/Window.h>

#define INTERUPT        (key == 'q' || key == 3)
#define tile(x, y)      map->array[y][x]
#define MOVE_TILE       tile(move.x, move.y)
#define CURENT_TILE     tile(obj.x, obj.y)
#define OUT_OF_MAP      move.x >= (int) map->x || move.y >= (int) map->y || \
                        move.x <= 0 || move.y <= 0
#define same_pos(a, b)  (a.x == b.x && a.y == b.y)

typedef struct textures
{
    sfTexture *box;
    sfTexture *floor;
    sfTexture *hole;
    sfTexture *player;
    sfTexture *wall;
} textures_t;

typedef enum direction
{
    up = 65,
    down = 66,
    right = 67,
    left = 68
} direction;


typedef struct int_vector
{
    int x;
    int y;
} vector2i;

typedef struct hole_list
{
    vector2i pos;
    struct hole_list *next;
} hole_l;

typedef struct map_struct
{
    char **array;
    size_t x;
    size_t y;
    int box_nbr;
    int hole_nbr;
    hole_l *holes;
} map_t;

int sokoban(int ac, char const **av);
void get_map(map_t *, const char *filename);
int game(map_t *, char const *filname);
vector2i move_obj(map_t *map, vector2i const player, int const key);
void add_nod(hole_l **head, vector2i pos);
sfRenderWindow *create_window(void);
sfSprite ***create_board(sfVector2i size);
textures_t *init_texture(void);
int is_end(map_t *map, vector2i player, sfRenderWindow *window, \
                                        char const *filename);
int display(sfRenderWindow *window, sfSprite ***board, map_t const *map, \
                                    textures_t *textures);

#endif /* !GRAPHICAL_SOKOBAN */