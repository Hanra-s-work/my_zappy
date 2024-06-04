/*
** EPITECH PROJECT, 2023
** my_zappy
** File description:
** utils.h
*/

#ifndef SERVER_UTILS_H
    #define SERVER_UTILS_H

    #include "arg_parse.h"

void free_array(void *to_free);

void free_args(struct arg_s **args, size_t size);

#endif //SERVER_UTILS_H
