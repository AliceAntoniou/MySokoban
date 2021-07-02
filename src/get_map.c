/*
** EPITECH PROJECT, 2021
** my sokoban
** File description:
** get map
*/

#include <stdio.h>
#include "my_lib.h"
#include "my_sokoban.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

static char *read_map(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    char *str = NULL;
    struct stat buf;

    if (fd == -1)
        return NULL;
    stat(filename, &buf);
    str = malloc(sizeof(char) * (buf.st_size + 1));
    read(fd, str, buf.st_size);
    str[buf.st_size] = '\0';
    return str;
}

static int get_map_size(map_t *map, char c, int tmp)
{
    if (c == '\n') {
        map->y++;
        if (tmp > (int) map->x)
            map->x = tmp;
        tmp = -1;
    }
    return tmp;
}

static void verify_map(map_t *map, char *buf)
{
    size_t i;
    map->box_nbr = 0;
    map->hole_nbr = 0;
    size_t tmp = 0;

    for (i = 0; my_is_in_str(buf[i], "#\n XOP") != -1; i++) {
        tmp = get_map_size(map, buf[i], tmp);
        if (buf[i] == 'X')
            map->box_nbr++;
        if (buf[i] == 'O')
            map->hole_nbr++;
        tmp++;
    }
    if (map->box_nbr != map->hole_nbr || map->hole_nbr == 0)
        map->y = 0;
    if (buf[i] != '\0')
        map->y = 0;
    return;
}

static void get_holes(map_t *map)
{
    map->holes = NULL;

    for (size_t y = 0; map->array[y] != NULL; y++)
        for (size_t x = 0; tile(x, y) != '\n' && tile(x, y) != '\0'; x++)
            if (tile(x, y) == 'O')
                add_nod(&map->holes, (vector2i) {x, y});
}

void get_map(map_t *map, const char *filename)
{
    char *buf = read_map(filename);

    map->array = NULL;
    if (!buf)
        return;
    map->x = 0;
    map->y = 0;
    verify_map(map, buf);
    if (map->y == 0)
        return;
    map->array = malloc(sizeof(char *) * (map->y + 1));
    if (map->array == NULL)
        return;
    for (size_t y = 0; buf != NULL; y++)
        map->array[y] = my_strtok(&buf, '\n');
    free(buf);
    get_holes(map);
    return;
}