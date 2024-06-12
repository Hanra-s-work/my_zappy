/*
** EPITECH PROJECT, 2023
** my_zappy
** File description:
** array_to_str.c
*/

#include <string.h>
#include <stdlib.h>

static size_t get_nb_word(char *str)
{
    size_t nb_word = 1;

    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] == ' ')
            ++nb_word;
    }
    return (nb_word);
}

static void fill_str(int ac, const char **av, char *str,
    int *quoted_string_index)
{
    int quoted_count = 0;

    for (int i = 0; i < ac; ++i) {
        if (quoted_string_index[quoted_count] == i)
            strcat(str, " ");
        strcat(str, av[i]);
        if (quoted_string_index[quoted_count] == i) {
            strcat(str, " ");
            ++quoted_count;
        }
    }
}

char *array_to_str(int ac, const char **av)
{
    char *str;
    size_t quoted_string = 0;
    size_t len = 0;
    int quoted_string_index[ac];

    memset(quoted_string_index, -1, sizeof(int) * 4);
    for (int i = 0; i < ac; ++i) {
        if (get_nb_word((char *)av[i]) > 1) {
            quoted_string_index[quoted_string] = i;
            ++quoted_string;
        }
        len += strlen(av[i]);
    }
    len += quoted_string * 2;
    str = malloc(sizeof(char) * (len + 1));
    if (str == NULL)
        return (NULL);
    str[0] = '\0';
    fill_str(ac, av, str, quoted_string_index);
    return (str);
}
