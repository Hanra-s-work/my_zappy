/*
** EPITECH PROJECT, 2023
** my_zappy
** File description:
** utils.c
*/

#include <unistd.h>
#include <string.h>

int write_error_msg(const char *str)
{
    write(STDERR_FILENO, str, strlen(str));
    return (-1);
}

int write_to_client(const int fd, const char *str)
{
    write(fd, str, strlen(str));
    return (0);
}
