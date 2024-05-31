/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** struct
*/

#pragma once

#include <sys/select.h>

/**
** @brief The structure to store every arguments passed to the program
**
** @param port The 
** @param argv 
** @return int
**/
typedef struct args_s {
    int port;
    int map_x;
    int map_y;
    char **name;
    int clients_nb;
    int frequence;
} args_t;

typedef struct server_utils_s {
    int socket;
    fd_set current_fd;
    fd_set ready_fd;
} server_utils_t;

typedef struct game_data_s {
    int map_size[2];
} game_data_t;

typedef struct sm_s {
    args_t arguments;
    server_utils_t utils;
    game_data_t data;
} sm_t;