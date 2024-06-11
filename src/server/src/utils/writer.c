/*
** EPITECH PROJECT, 2023
** my_zappy
** File description:
** utils.c
*/

#include <unistd.h>
#include <string.h>

int write_error_msg(char *str)
{
    write(STDERR_FILENO, str, strlen(str));
    return (-1);
}
