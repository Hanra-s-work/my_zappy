/*
** EPITECH PROJECT, 2024
** my_zappy
** File description:
** command_parse.h
*/

#ifndef MY_ZAPPY_COMMAND_PARSE_H
    #define MY_ZAPPY_COMMAND_PARSE_H

    #include <stdint.h>

/**
 * @brief Parse read buffer from server to command
 * @param buffer Read buffer from server
 * @param buf_size Size of buffer
 * @return If command is valid return splited command else return NULL
 */
char **parse_command(uint8_t *buffer, ssize_t buf_size);

/**
 * @brief Get all command in buffer (a command is delimited by \n)
 * @param buffer
 * @param buf_size
 * @return
 */
char ***parse_buffer(uint8_t *buffer, ssize_t buf_size);

#endif //MY_ZAPPY_COMMAND_PARSE_H
