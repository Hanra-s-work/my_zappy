/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** constants
*/

#ifndef SERVER_CONSTANTS_H
    #define SERVER_CONSTANTS_H

    //!! GLOBAL CONSTANTS !!

    #define ERROR 84
    #define MAX_BUFFER_SIZE 1024
    #define MAX_CLIENT 1024
    #define UNKNOWN -1

    //!! PARSING CONSTANTS !!

    #define NB_PARAM 6
    #define CLIENTS_NB_PARAM "number of authorized clients per team"
    #define FREQUENCE_PARAM "reciprocal of time unit for execution of actions"
    #define MINIMUM_MAP_SIZE 20

    //!! INITIALIZATION VALUE CONSTANTS !!

    #define DEFAULT_FREQUENCE 100

    // Ressources density

    #define FOOD_DENSITY 0.5
    #define LINEMATE_DENSITY 0.3
    #define DERAUMERE_DENSITY 0.15
    #define SIBUR_DENSITY 0.1
    #define MENDIANE_DENSITY 0.1
    #define PHIRAS_DENSITY 0.08
    #define THYSTAME_DENSITY 0.05

    // Time

    #define SPAWNS_TIME 20
    #define PLAYER_TIME 1260
    #define ADD_FOOD 126
    #define BASIC_TIME 7
    #define INVENTORY_TIME 1
    #define FORK_TIME 42
    #define INCANTATION_TIME 300
    #define COMMAND_DELIMITER   " "
    #define COMMAND_SEPARATOR   "\n"

    // !! COMMAND_CONSTANT !!

    #define CLIENT_COMMAND_NB   13
    #define GUI_COMMAND_NB      9
    #define BROADCAST_COMMAND   5

#endif
