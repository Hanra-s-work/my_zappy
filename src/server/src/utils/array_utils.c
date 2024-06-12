/*
** EPITECH PROJECT, 2023
** my_zappy
** File description:
** array_utils.c
*/

#include <string.h>
#include <stdlib.h>

size_t get_array_len(char **array)
{
    size_t len = 0;

    for (; array[len] != NULL; ++len) {}
    return (len);
}

void free_array(void *to_free)
{
    void **array = (void **)to_free;

    for (int i = 0; array[i] != NULL; ++i) {
        free(array[i]);
    }
}

void free_array_size_n(void *to_free, size_t n)
{
    void **array = (void **)to_free;

    for (size_t i = 0; i < n; ++i) {
        free(array[i]);
    }
}

char **str_to_word_array(char *str, const char *delim)
{
    int array_size = 1;
    char *buf;
    char **array = NULL;
    char **new_array = NULL;

    buf = strtok(str, delim);
    for (; buf != NULL; ++array_size) {
        new_array = realloc(array, sizeof(char *) * (array_size + 1));
        if (new_array == NULL)
            return (NULL);
        array[array_size] = malloc(sizeof(char) * (strlen(buf) + 1));
        if (array[array_size] == NULL) {
            free_array_size_n(array, array_size - 1);
            return (NULL);
        }
        (void) strcpy(array[array_size], buf);
        buf = strtok(str, delim);
    }
    array[array_size] = NULL;
    return (array);
}
