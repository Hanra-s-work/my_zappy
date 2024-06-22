/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** check_values_validity
*/

#include <string.h>

#include "utils.h"
#include "arg_parse.h"

static int number_checker(const struct arg_s **arguments, const int index)
{
    char str[MAX_BUFFER_SIZE];
    char *num_str = (char *)arguments[index]->value;

    if (strcmp(arguments[index]->name, "-n") == 0)
        return (0);
    if (strlen(num_str) == 1 && strcmp(num_str, "0") == 0) {
        strcpy(str, "Error: The number of the parameter '");
        strcat(str, arguments[index]->name);
        strcat(str, "' must be greater than 0.\n");
        return (write_error_msg(str));
    }
    for (int i = 0; num_str[i] != '\0'; i++) {
        if (num_str[i] < '0' || num_str[i] > '9') {
            strcpy(str, "Error: The parameter '");
            strcat(str, arguments[index]->name);
            strcat(str, "' must be a number.\n");
            return (write_error_msg(str));
        }
    }
    return (0);
}

static int compare_name_2(char **array, const char *name, const size_t x)
{
    char str[MAX_BUFFER_SIZE];

    for (size_t i = 0; i < x; i++) {
        if (array[i] == NULL) {
            break;
        }
        if (strcmp(name, array[i]) == 0) {
            strcpy(str, "Error: The team name '");
            strcat(str, name);
            strcat(str, "' is repeated. A team name must be unique.\n");
            return (write_error_msg(str));
        }
    }
    return (0);
}

static int compare_name_1(const struct arg_s **arguments, const size_t index)
{
    char **tmp = NULL;
    char **name = NULL;
    size_t x = 0;

    name = arguments[index]->value;
    tmp = malloc(sizeof(char *) * arguments[index]->nb_value + 1);
    for (size_t i = 0; i < arguments[index]->nb_value; i++) {
        if (compare_name_2(tmp, *name, x) == -1) {
            free(tmp);
            return (-1);
        }
        tmp[x] = *name;
        x++;
        name++;
    }
    free(tmp);
    return (0);
}

static int name_checker(const struct arg_s **arguments, const size_t index)
{
    if (strcmp(arguments[index]->name, "-n") != 0) {
        return (0);
    }
    if (arguments[index]->nb_value > 1) {
        if (compare_name_1(arguments, index) == -1) {
            return (-1);
        }
    }
    return (0);
}

static int map_size_checker(const struct arg_s **arguments)
{
    char str[MAX_BUFFER_SIZE];
    int x = 0;
    int y = 0;

    strcpy(str, (char *)find_value_by_param(arguments, "-x"));
    x = atoi(str);
    strcpy(str, (char *)find_value_by_param(arguments, "-y"));
    y = atoi(str);
    if (x < 15 || x > 300) {
        write_error_msg("Error: The x value must be between 15 and 300.\n");
        return (-1);
    }
    if (y < 10 || y > 300) {
        write_error_msg("Error: The y value must be between 10 and 300.\n");
        return (-1);
    }
    return (0);
}

int check_values_validity(const struct arg_s **arguments, const size_t size)
{
    for (size_t i = 0; i < size; i++) {
        if (number_checker(arguments, i) == -1) {
            return (-1);
        }
        if (name_checker(arguments, i) == -1) {
            return (-1);
        }
    }
    return map_size_checker(arguments);
}
