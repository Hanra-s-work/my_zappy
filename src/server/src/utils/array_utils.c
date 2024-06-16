/*
** EPITECH PROJECT, 2023
** my_zappy
** File description:
** array_utils.c
*/

#include <string.h>
#include <stdlib.h>

#include "utils.h"

size_t get_array_len(char **array)
{
    size_t len = 0;

    for (; array[len] != NULL; ++len);
    return (len);
}

static int count_string_character(const char *str, const char delim)
{
    int count = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != delim) {
            count++;
        } else {
            return (count);
        }
    }
    return (count);
}

static int count_string_number(const char *str, const char delim)
{
    int count = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == delim) {
            count++;
        }
    }
    count++;
    return (count);
}

static int jump_n(const int n, const int size, const char *str,
    const char delim)
{
    int new_n = size + n;

    while (str[new_n] == '\0' || str[new_n] == delim) {
        if (str[new_n] == '\0') {
            return (new_n);
        }
        new_n = new_n + 1;
    }
    return (new_n);
}

char **str_to_word_array(const char *str, const char delim)
{
    int count = count_string_number(str, delim);
    char **tab = malloc(sizeof(char *) * (count + 1));
    int n = 0;
    int line = 0;
    int size = 0;

    if (tab == NULL)
        return (NULL);
    while (str[n] != '\0' && line < count) {
        size = count_string_character(str + n, delim);
        tab[line] = malloc(sizeof(char) * (size + 1));
        if (tab[line] == NULL)
            return (NULL);
        strncpy(tab[line], str + n, size);
        tab[line][size] = '\0';
        line++;
        n = jump_n(n, size, str, delim);
    }
    tab[line] = NULL;
    return (tab);
}
