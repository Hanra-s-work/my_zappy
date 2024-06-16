/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** show
*/

#ifndef SHOW_H_
    #define SHOW_H_

    #include "server_handler.h"

/**
 * @brief A function to display every data of the game
 * @param server The general server structure
 * @param need_to_show (true) if we want to show it, (false) if not
*/
int show_game_data(server_handler_t *server, bool need_to_show);

#endif
