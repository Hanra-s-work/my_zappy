/*
** EPITECH PROJECT, 2024
** server
** File description:
** client_management
*/

#ifndef CLIENT_MANAGEMENT_H_
    #define CLIENT_MANAGEMENT_H_

    #include "server_handler.h"

/**
 * @brief The function to initialize the cli_t structure
 * @param client The cli_t structure to initialize
*/
void init_client(cli_t client[MAX_CLIENT]);

/**
 * @brief The function to get the client index in the structure by the fd
 * @param client The cli_t structure
 * @param fd The file descriptor of the client
 * @return int: The index where the fd is stored
*/
int get_client(cli_t client[MAX_CLIENT], const int fd);

/**
 * @brief The function to delete a specific client from the cli_t structure by
 * the fd
 * @param clint The cli_t structure
 * @param fd The file descriptor of the client
 * @return (0) if the client is founded and deleted successfully, (-1) if not
*/
int delete_client(cli_t client[MAX_CLIENT], const int fd);

/**
 * @brief The function to delete a every client from the cli_t structure
 * @param clint The cli_t structure
*/
void delete_all_client(cli_t client[MAX_CLIENT]);

#endif
