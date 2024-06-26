/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** ai_event
*/

#ifndef AI_EVENT_H_
    #define AI_EVENT_H_

    #include "server_handler.h"

// EVENT UTILS

void delete_event(event_t *event);

void delete_all_event(event_t event[MAX_EVENT]);

int send_success(game_data_t *game, const int i, const int idx,
    const bool is_start);

int check_incantation_condition(game_data_t *game, const int i, const int idx,
    const bool is_start);

void go_in_good_direction(game_data_t *game, const int idx, int *x, int *y);

void do_other_look(server_handler_t *server, char str[INSANE_BUFFER_SIZE],
    const int idx);

void generic_look(server_handler_t *server,
    char str[INSANE_BUFFER_SIZE], const int idx, const int size);

void delete_client_current_event(server_handler_t *server, const int fd);



// COMMAND ADDER

int add_broadcast(server_handler_t *server, char **parsed_command,
    const int idx);

int add_eject(server_handler_t *server, char **parsed_command,
    const int idx);

int add_fork(server_handler_t *server, char **parsed_command,
    const int idx);

int add_forward(server_handler_t *server, char **parsed_command,
    const int idx);

int add_incantation(server_handler_t *server, char **parsed_command,
    const int idx);

int add_inventory(server_handler_t *server, char **parsed_command,
    const int idx);

int add_left(server_handler_t *server, char **parsed_command,
    const int idx);

int add_look(server_handler_t *server, char **parsed_command,
    const int idx);

int add_right(server_handler_t *server, char **parsed_command,
    const int idx);

int add_set(server_handler_t *server, char **parsed_command,
    const int idx);

int add_take(server_handler_t *server, char **parsed_command,
    const int idx);

// COMMAND LAUNCHER

int do_connect(server_handler_t *server, char **parsed_command,
    const int idx);

void do_broadcast(server_handler_t *server, event_t event);

void do_eject(server_handler_t *server, event_t event);

void do_forward(server_handler_t *server, event_t event);

void do_fork(server_handler_t *server, event_t event);

void do_left(server_handler_t *server, event_t event);

void do_look(server_handler_t *server, event_t event);

void do_right(server_handler_t *server, event_t event);

void do_set(server_handler_t *server, event_t event);

void do_take(server_handler_t *server, event_t event);

void do_inventory(server_handler_t *server, event_t event);

#endif /* !AI_EVENT_H_ */
