/*
** EPITECH PROJECT, 2024
** server
** File description:
** command_handling
*/

#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "utils.h"
#include "command_parse.h"
#include "server_handler.h"
#include "client_management.h"

static int search_in_queue(server_handler_t *server, const int fd)
{
    for (int i = 0; i < MAX_CLIENT; i++) {
        if (server->fd_queue[i] == fd) {
            return (fd);
        }
    }
    return (-1);
}

static void remove_fd_from_queue(server_handler_t *server, const int fd)
{
    for (int i = 0; i < MAX_CLIENT; i++) {
        if (server->fd_queue[i] == fd) {
            server->fd_queue[i] = UNKNOWN;
            return;
        }
    }
}

static void set_gui_client(server_handler_t *server, const int fd)
{
    for (int i = 0; i < MAX_CLIENT; i++) {
        if (server->game_data.clients[i].client_num == UNKNOWN) {
            server->game_data.clients[i].fd = fd;
            server->game_data.clients[i].team_name = strdup(GUI_TEAM_NAME);
            remove_fd_from_queue(server, fd);
            return;
        }
    }
}

static int search_team_name(server_handler_t *server,
    const char buffer[MAX_BUFFER_SIZE])
{
    bool is_found = false;

    for (int i = 0; server->game_data.teams[i].team_name != NULL; i++) {
        if (strncmp(buffer, server->game_data.teams[i].team_name,
        strlen(server->game_data.teams[i].team_name) - 1) == 0) {
            is_found = true;
            break;
        }
    }
    if (is_found == false) {
        return (-1);
    }
    return (0);
}

static void set_ai_client(server_handler_t *server,
    const char buffer[MAX_BUFFER_SIZE], const int fd)
{
    char str[MAX_BUFFER_SIZE];

    for (int i = 0; i < MAX_CLIENT; i++) {
        if (strncmp(server->game_data.clients[i].team_name, buffer,
        strlen(buffer) - 1) == 0 &&
        server->game_data.clients[i].fd == UNKNOWN) {
            server->game_data.clients[i].fd = fd;
            server->game_data.clients[i].is_connected = true;
            memset(str, '\0', MAX_BUFFER_SIZE);
            sprintf(str, "%d\n", server->game_data.clients[i].client_num);
            write_to_client(fd, str);
            memset(str, '\0', MAX_BUFFER_SIZE);
            sprintf(str, "%d %d\n", server->game_data.map_size[0],
            server->game_data.map_size[1]);
            write_to_client(fd, str);
            remove_fd_from_queue(server, fd);
            break;
        }
    }
}

static void check_which_command(server_handler_t *server,
    char **parsed_command, const int idx)
{
    for (int i = 0; i < GUI_COMMAND_NB + CLIENT_COMMAND_NB; i++) {
        if (COMMAND_TABLE[i].command_fct == NULL) {
            continue;
        }
        if (strcmp(parsed_command[0], COMMAND_TABLE[i].command) == 0) {
            COMMAND_TABLE[i].command_fct(server, parsed_command, idx);
        }
    }
}

static void check_inside_buffer(server_handler_t *server,
    const char buffer[MAX_BUFFER_SIZE], const int idx)
{
    char ***parsed_buffer = parse_buffer((unsigned char *)buffer,
    strlen(buffer) + 1);

    if (parsed_buffer == NULL) {
        write_to_client(server->game_data.clients[idx].fd, UNKNOWN_COMMAND);
        return;
    }
    for (int i = 0; parsed_buffer[i] != NULL; i++) {
        check_which_command(server, parsed_buffer[i], idx);
    }
    for (int i = 0; parsed_buffer[i] != NULL; i++) {
        free_array(parsed_buffer[i]);
    }
    free(parsed_buffer);
}

static void launch_command(server_handler_t *server,
    const char buffer[MAX_BUFFER_SIZE], const bool is_in_queue, const int idx)
{
    if (is_in_queue == true) {
        if (strncmp(buffer, GUI_TEAM_NAME, strlen(GUI_TEAM_NAME)) == 0) {
            set_gui_client(server, idx);
            return;
        }
        if (search_team_name(server, buffer) == 0) {
            set_ai_client(server, buffer, idx);
            return;
        }
        write_to_client(idx, UNKNOWN_COMMAND);
        return;
    }
    if (strlen(buffer) < 2) {
        write_to_client(server->game_data.clients[idx].fd, UNKNOWN_COMMAND);
        return;
    }
    check_inside_buffer(server, buffer, idx);
}

void command_handling(server_handler_t *server, const int fd)
{
    char buffer[MAX_BUFFER_SIZE];
    ssize_t read_bytes = 0;
    int idx = get_client(server->game_data.clients, fd);
    bool is_in_queue = false;

    if (idx == -1) {
        idx = search_in_queue(server, fd);
        if (idx == -1)
            return;
        is_in_queue = true;
    }
    memset(buffer, '\0', MAX_BUFFER_SIZE);
    read_bytes = read(fd, buffer, sizeof(buffer));
    if (read_bytes <= 0) {
        FD_CLR(fd, &server->current_fd);
        delete_client(server->game_data.clients, fd);
        printf("The client %d has been deconnected.\n", fd);
        return;
    }
    launch_command(server, buffer, is_in_queue, idx);
}
