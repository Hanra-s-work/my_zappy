/*
** EPITECH PROJECT, 2023
** my_zappy
** File description:
** utils.c
*/
#include <stdlib.h>
#include <stdio.h>

void free_array(void *to_free)
{
    void **array = (void **)to_free;

    for (int i = 0; array[i] != NULL; ++i) {
        free(array[i]);
    }
}
