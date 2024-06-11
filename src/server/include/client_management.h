/*
** EPITECH PROJECT, 2024
** server
** File description:
** client_management
*/

#ifndef CLIENT_MANAGEMENT_H_
    #define CLIENT_MANAGEMENT_H_

    #include "server_handler.h"

void init_client(cli_t client[MAX_CLIENT]);
int get_client(cli_t client[MAX_CLIENT], const int fd);
int delete_client(cli_t client[MAX_CLIENT], const int fd);
void delete_all_client(cli_t client[MAX_CLIENT]);

#endif
