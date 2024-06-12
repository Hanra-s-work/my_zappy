/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** struct
*/

#ifndef SERVER_HANDLER_H
    #define SERVER_HANDLER_H

    #include <sys/select.h>

    #include "arg_parse.h"

/* Important informations:
** - Ressources spawns every 20 units of times
** - Ressource quantity formula: map_width * map_height * density
** - A player time life start is 1260 / f
** - One food add to the time life of a player 126 units of time
** - A player starts with a random direction
*/

typedef enum ressources_type_s {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
} ressources_type_t;

typedef enum direction_s {
    UNDEFINED,
    LEFT,
    RIGHT,
    UP,
    DOWN
} direction_t;

typedef struct ressources_s {
    int food_nb;
    int linemate_nb;
    int deraumere_nb;
    int sibur_nb;
    int mendiane_nb;
    int phiras_nb;
    int thystame_nb;
} ressources_t;

typedef struct cli_s {
    int fd;
    bool is_connected;
    char *team_name;
    int client_num; // Client numero in the team
    int level;
    int pos[2]; // Client position in the map (0 = x, 1 = y)
    ressources_t ressources; // User inventory
    int time_life;
    direction_t direction;
} cli_t;

typedef struct map_s {
    int player_nb;
    ressources_t ressources;
} map_t;

typedef struct team_s {
    char *team_name;
    int client_total;
    int client_num_list[MAX_CLIENT];
} team_t;

typedef struct game_data_s {
    int map_size[2]; // 0 = x, 1 = y
    int frequence;
    // The max number, a ressource can have in the map
    ressources_t ressources_quantity;
    ressources_t total_ressources; // All the ressources in the map
    team_t *teams;
    cli_t clients[MAX_CLIENT];
    map_t **map;
} game_data_t;

typedef struct server_handler_s {
    int socket;
    fd_set current_fd;
    fd_set ready_fd;
    game_data_t game_data;
} server_handler_t;

static const ressources_t DEFAULT_RESSOURCES = {
    0, // Food
    0, // Linemate
    0, // Deraumere
    0, // Sibur
    0, // Mendiane
    0, // Phiras
    0  // Thystame
};

static const cli_t DEFAULT_CLIENT = {
    UNKNOWN, // Fd
    false,   // Is_connected
    NULL,    // Team name
    UNKNOWN, // Client num
    UNKNOWN, // Level
    { UNKNOWN, UNKNOWN }, // Pos
    { 0, 0, 0, 0, 0, 0, 0}, // Inventory
    UNKNOWN, // Time life
    UNDEFINED // Direction
};

int init_game_data(server_handler_t *server, struct arg_s **arguments);
int server_initialization(server_handler_t *server, struct arg_s **arguments);

#endif
