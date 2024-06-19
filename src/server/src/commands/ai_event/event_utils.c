/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** event_utils
*/

#include "utils.h"
#include "server_handler.h"

void delete_event(event_t *event)
{
    event->fd = UNKNOWN;
    event->time_counter = UNKNOWN;
    event->type = UNKNOWN_TYPE;
    free_array(event->args);
    if (event->indexes != NULL) {
        free(event->indexes);
    }
}

void delete_all_event(event_t event[MAX_EVENT])
{
    for (int i = 0; i < MAX_EVENT; i++) {
        if (event[i].fd != UNKNOWN) {
            delete_event(&event[i]);
        }
    }
}
