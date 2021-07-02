/*
** EPITECH PROJECT, 2021
** my sokoban
** File description:
** sokoban
*/

#ifndef MY_SOKOBAN_H_
#define MY_SOKOBAN_H_

#include <unistd.h>

#define INTERUPT        (key == 'q' || key == 3)
#define tile(x, y)      map->array[y][x]
#define MOVE_TILE       tile(move.x, move.y)
#define CURENT_TILE     tile(obj.x, obj.y)
#define OUT_OF_MAP      move.x >= (int) map->x || move.y >= (int) map->y - 1 ||\
                        move.x <= 0 || move.y <= 0
#define same_pos(a, b)  (a.x == b.x && a.y == b.y)

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
int is_end(map_t *map, vector2i player, int key, char const *filename);

#endif /* !MY_SOKOBAN_H_ */