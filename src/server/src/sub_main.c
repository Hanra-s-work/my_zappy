/*
** EPITECH PROJECT, 2023
** my_zappy [fed34_prox_vm]
** File description:
** sub_main.c
*/

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#include "utils.h"
#include "arg_parse.h"
#include "client_management.h"

static int display_helper(void)
{
    printf("USAGE:\n"
    "\t./zappy_server -p port -x width -y height -n name1 name2 ... "
    "-c clientNb -f freq\n\n"
    "DESCRIPTION:\n"
    "\t-p port             [MANDATORY] port number\n"
    "\t-x width            [MANDATORY] width of the world\n"
    "\t-y height           [MANDATORY] height of the world\n"
    "\t-n name1 name2 ...  [MANDATORY] name of the team\n"
    "\t-c clientNb         [MANDATORY] number of authorized clients per team\n"
    "\t-f freq             [OPTIONAL]  reciprocal of time unit "
    "for execution of actions\n");
    return (0);
}

static int shutdown_server(server_handler_t *server)
{
    if (server->game_data.map != NULL) {
        free_array(server->game_data.map);
    }
    if (server->game_data.teams != NULL) {
        for (int i = 0; server->game_data.teams[i].team_name != NULL; i++) {
            free(server->game_data.teams[i].team_name);
        }
        free(server->game_data.teams);
    }
    delete_all_client(server->game_data.clients);
    if (shutdown(server->socket, SHUT_RDWR) == -1) {
        return (ERROR);
    }
    return (0);
}

static int arguments_handler(int argc, char **argv, server_handler_t *server)
{
    struct arg_s **arguments = NULL;
    int nb_param = get_nb_parameter(argc, (const char **)argv);

    arguments = get_zappy_args(argc, (const char **)argv, SERVER_OPTION);
    if (arguments == NULL) {
        return write_error_msg("See the helper with '-help' option.\n");
    }
    if (check_values_validity((const struct arg_s **)arguments,
    nb_param) == -1) {
        free_args(arguments, nb_param);
        return (-1);
    }
    if (server_initialization(server, arguments) == -1) {
        free_args(arguments, nb_param);
        return (-1);
    }
    free_args(arguments, nb_param);
    return (0);
}

int sub_main(int argc, char **argv)
{
    server_handler_t server;

    srand(time(NULL));
    if (argc == 2 && strcmp(argv[1], "-help") == 0) {
        return display_helper();
    }
    if (arguments_handler(argc, argv, &server) == -1) {
        return (ERROR);
    }
    server_loop(&server);
    return (shutdown_server(&server));
}
