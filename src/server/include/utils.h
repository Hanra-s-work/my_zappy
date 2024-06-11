/*
** EPITECH PROJECT, 2023
** my_zappy
** File description:
** utils.h
*/

#ifndef SERVER_UTILS_H
    #define SERVER_UTILS_H

    #include "arg_parse.h"

int write_error_msg(char *str);

/**
 * @brief Get array len
 * @param array
 * @return
 */
size_t get_array_len(char **array)

/**
 * @brief Free any ** array
 * @param to_free
 */
void free_array(void *to_free);

/**
 * @brief Free struct args_s of lenght size
 * @param args structure to free
 * @param size size of structure
 */
void free_args(struct arg_s **args, size_t size);

/**
 * @brief Free any ** array up to n
 * @attention if n is superior to the array size the behaviour is undefined
 * @param to_free
 * @param n
 */
void free_array_size_n(void *to_free, size_t n);

/**
 * @brief Turn string to char **
 * @param str
 * @param delim
 * @return splited string
 */
char **str_to_word_array(char *str, const char *delim);

#endif //SERVER_UTILS_H
