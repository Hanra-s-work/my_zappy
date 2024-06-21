/*
** EPITECH PROJECT, 2023
** my_zappy
** File description:
** utils.c
*/

#include <unistd.h>
#include <string.h>

#include "server_handler.h"

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

void write_to_graphics_clients(const cli_t clients[MAX_CLIENT],
    const char *str)
{
    for (int i = 0; i < MAX_CLIENT; i++) {
        if (clients[i].fd == UNKNOWN) {
            continue;
        }
        if (strcmp(clients[i].team_name, GUI_TEAM_NAME) == 0) {
            write_to_client(clients[i].fd, str);
        }
    }
}

void write_unknown_command(const cli_t client)
{
    if (strcmp(client.team_name, GUI_TEAM_NAME) == 0) {
        write_to_client(client.fd, GUI_UNKNOWN);
    } else {
        write_to_client(client.fd, AI_COMMAND_FAILED);
    }
}
