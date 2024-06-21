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
    #define INSANE_BUFFER_SIZE 5000
    #define MAX_CLIENT 1024
    #define UNKNOWN -1

    //!! PARSING CONSTANTS !!

    #define NB_PARAM 6
    #define CLIENTS_NB_PARAM "number of authorized clients per team"
    #define FREQUENCE_PARAM "reciprocal of time unit for execution of actions"

    //!! INITIALIZATION VALUE CONSTANTS !!

    #define DEFAULT_FREQUENCE 100
    #define MAX_EVENT 2000

    // Ressources density

    #define FOOD_DENSITY 0.5
    #define LINEMATE_DENSITY 0.3
    #define DERAUMERE_DENSITY 0.15
    #define SIBUR_DENSITY 0.1
    #define MENDIANE_DENSITY 0.1
    #define PHIRAS_DENSITY 0.08
    #define THYSTAME_DENSITY 0.05

    // Time

    #define SPAWN_TIME 20
    #define PLAYER_TIME 1260
    #define ADD_TIME_LIFE 126
    #define BASIC_TIME 7
    #define INVENTORY_TIME 1
    #define FORK_TIME 42
    #define INCANTATION_TIME 300

    // !! COMMAND_CONSTANT !!

    #define COMMAND_DELIMITER   ' '
    #define COMMAND_SEPARATOR   '\n'

    #define AI_COMMAND_NB   12
    #define GUI_COMMAND_NB      9
    #define BROADCAST_COMMAND   5

    #define GUI_TEAM_NAME "GRAPHIC"

    //!! MESSAGE !!

    #define CONNEXION_FAILED "Failed to get connexion with the client.\n"
    #define AI_COMMAND_FAILED "ko\n"
    #define GUI_UNKNOWN_COMMAND "suc\n"
    #define ELEVATION_UNDERWAY "Elevation underway\n"
    #define AI_DIED "dead\n"
    #define ALL_FINE "ok\n"

#endif
