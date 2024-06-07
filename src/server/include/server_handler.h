/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** struct
*/

#ifndef SERVER_HANDLER_H
    #define SERVER_HANDLER_H

    #include <sys/select.h>

typedef struct server_handler_s {
    int socket;
    fd_set current_fd;
    fd_set ready_fd;
} server_handler_t;

#endif
