/*
** EPITECH PROJECT, 2023
** my_zappy
** File description:
** utils.h
*/

#ifndef SERVER_UTILS_H
    #define SERVER_UTILS_H

    #include "arg_parse.h"
    #include "server_handler.h"

// Writer

int write_error_msg(char *str);

// Finder

void *find_value_by_param(const struct arg_s **arguments, char *param);

int find_index_by_param(const struct arg_s **arguments, char *param);

// Free

void free_array(void *to_free);

void free_args(struct arg_s **args, size_t size);

// Fill

void refill_map(game_data_t *game_data);

void fill_map(server_handler_t *server);

#endif //SERVER_UTILS_H
