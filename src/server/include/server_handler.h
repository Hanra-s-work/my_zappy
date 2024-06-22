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

// An enum type to enum every ressources in the game
typedef enum ressources_type_s {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
} ressources_type_t;

// An enum type to enum every player directions in the game
typedef enum direction_s {
    UNDEFINED,
    UP,
    RIGHT,
    DOWN,
    LEFT
} direction_t;

// An enum type to enum every possible event in the game
typedef enum event_type_s {
    UNKNOWN_TYPE,
    FORWARD,
    RIGHT_EVENT,
    LEFT_EVENT,
    LOOK,
    INVENTORY,
    BROADCAST,
    CONNECT_NBR,
    FORK,
    EJECT,
    TAKE,
    SET,
    INCANTATION,
    FOOD_REGEN
} event_type_t;

/** @brief A structure to count ressources in the game
 * @param food_nb
 * @param linemate_nb
 * @param deraumere_nb
 * @param sibur_nb
 * @param mendiane_nb
 * @param phiras_nb
 * @param thystame_nb
 */
typedef struct ressources_s {
    int food_nb;
    int linemate_nb;
    int deraumere_nb;
    int sibur_nb;
    int mendiane_nb;
    int phiras_nb;
    int thystame_nb;
} ressources_t;

/** @brief A structure to store every client/player data
 * @param fd The file descriptor of the client
 * @param is_connected Is he connected to the server
 * @param team_name The team where he is
 * @param client_num His numero in the team
 * @param level His level in the game
 * @param pos His position in the map (0 = x, 1 = y)
 * @param ressources His inventory
 * @param time_life His time life
 * @param direction His direction (LEFT, RIGHT, UP, DOWN)
 */
typedef struct cli_s {
    int fd;
    bool is_connected;
    char *team_name;
    int client_num;
    int level;
    int pos[2];
    ressources_t ressources;
    int time_life;
    direction_t direction;
} cli_t;

/**
 * @brief A structure to store every tiles content (Must be an 2D array)
 * @param player_nb The number of player in a tile
 * @param ressources The number of ressourcees in a tile
*/
typedef struct map_s {
    int player_nb;
    ressources_t ressources;
} map_t;

/**
 * @brief A structure to store every team data
 * @param team_name The name of the team
 * @param client_total The total number of client it has
 * @param clint_num_list The list of every client number
 * (Refer to "client_num" in cli_t structure)
*/
typedef struct team_s {
    char *team_name;
    int client_total;
    int client_num_list[MAX_CLIENT];
} team_t;

typedef struct event_s {
    int fd;
    event_type_t type;
    char **args;
    int time_counter;
    int *indexes;
} event_t;

/**
 * @brief A structure to store the game data
 * @param map_size The size of the map (x = 0, y = 1)
 * @param frequence The frequence passed in parameter
 * @param ressources_quantity The max number, a ressource can have in the map
 * @param total_ressources All the ressources in the map
 * @param teams Every team data
 * @param clients Every client data
 * @param map Map content
*/
typedef struct game_data_s {
    int map_size[2];
    int frequence;
    double time;
    ressources_t ressources_quantity;
    ressources_t total_ressources;
    team_t *teams;
    cli_t clients[MAX_CLIENT];
    map_t **map;
    event_t event[MAX_EVENT];
} game_data_t;

/**
 * @brief A structure to store server general data
 * @param socket The socket of the server for the connexion
 * @param current_fd Every fd storage
 * @param ready_fd Usable fd for select function
 * @param game_data The game data
 * @param fd_queue The queue to wait a fd to give his team name
*/
typedef struct server_handler_s {
    int socket;
    fd_set current_fd;
    fd_set ready_fd;
    game_data_t game_data;
    int fd_queue[MAX_CLIENT];
} server_handler_t;

// A constant to set a "ressource_t" structure to default values
static const ressources_t DEFAULT_RESSOURCES = {
    0, // Food
    0, // Linemate
    0, // Deraumere
    0, // Sibur
    0, // Mendiane
    0, // Phiras
    0  // Thystame
};

// A constant to set a "cli_t" structure to default values
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

static const event_t DEFAULT_EVENT = {
    UNKNOWN, // fd
    UNKNOWN_TYPE, // Event type
    NULL, // Command arguments
    UNKNOWN, // Time counter
    NULL // Indexes
};

/**
 * @brief The function to initialize every game data
 * @param server The general server structure
 * @param arguments All parsed arguments passed as program parameter
 * @return (0) if datas are initialized successfully, (-1) if not
*/
int init_game_data(server_handler_t *server, struct arg_s **arguments);

/**
 * @brief The function to initialize every server data
 * @param server The general server structure
 * @param arguments All parsed arguments passed as program parameter
 * @return (0) if datas are initialized successfully, (-1) if not
*/
int server_initialization(server_handler_t *server, struct arg_s **arguments);

/**
 * @brief The server loop where communication client/server can be done
 * @param server The general server structure
*/
void server_loop(server_handler_t *server);

/**
 * @brief Handle client message/command
 * @param server The general server structure
 * @param fd The file descriptor where the message come from
*/
void command_handling(server_handler_t *server, const int fd);

/**
 * @brief Check every event in the game
 * @param server A pointer to the server_handler_t structure
*/
void check_event(server_handler_t *server);

#endif
