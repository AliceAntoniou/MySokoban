/*
** EPITECH PROJECT, 2020
** my params to list
** File description:
** put params in a list
*/

#include <stdlib.h>
#include <stdio.h>
#include "my_lib.h"

void add_nod(linked_list_t **head, void *av)
{
    linked_list_t *node = malloc(sizeof(linked_list_t));

    if (*head == NULL) {
        node->data = av;
        node->next = NULL;
        (*head) = node;
        return;
    }
    node->data = av;
    node->next = (*head);
    (*head) = node;
    return;
}

linked_list_t *my_params_to_list(int ac, char * const *av)
{
    linked_list_t *head = 0;
    int i = 0;

    while (i < ac) {
        add_nod(&head, av[i]);
        i++;
    }
    return (head);
}