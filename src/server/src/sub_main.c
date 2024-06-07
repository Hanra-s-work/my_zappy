/*
** EPITECH PROJECT, 2023
** my_zappy [fed34_prox_vm]
** File description:
** sub_main.c
*/

#include <string.h>
#include <stdio.h>

#include "arg_parse.h"
#include "utils.h"

static int display_helper(void)
{
    printf("USAGE:\n"
    "\t./zappy_server -p port -x width -y height -n name1 name2 ..."
    "-c clientNb -f freq\n\n"
    "DESCRIPTION:\n"
    "\t-p port             port number\n"
    "\t-x width            width of the world\n"
    "\t-y height           height of the world\n"
    "\t-n name1 name2 ...  name of the team\n"
    "\t-c clientNb         number of authorized clients per team\n"
    "\t-f freq             reciprocal of time unit for execution of actions\n");
    return (0);
}

int sub_main(int argc, char **argv)
{
    struct arg_s **arguments = NULL;

    if (argc == 2 &&
    (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "-help") == 0 ||
    strcmp(argv[1], "--help") == 0)) {
        return display_helper();
    }
    arguments = get_zappy_args(argc, (const char **)argv, SERVER_OPTION);
    if (arguments == NULL) {
        display_helper();
        return (ERROR);
    }
    free_args(arguments, (argc / 2));
    return (0);
}
