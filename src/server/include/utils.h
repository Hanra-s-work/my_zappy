/*
** EPITECH PROJECT, 2023
** my_zappy
** File description:
** utils.h
*/

#ifndef SERVER_UTILS_H
    #define SERVER_UTILS_H

    #include "arg_parse.h"
    #include "server_handler.h"

//!! WRITTER !!

/**
 * @brief Write any message in the error output
 * @param str The string we want to write
 * @return (-1)
*/
int write_error_msg(const char *str);

/**
 * @brief Write any message to a specific file descriptor
 * @param fd The file descriptor where we want to write
 * @param str The string we want to write
 * @return (0)
*/
int write_to_client(const int fd, const char *str);

/**
 * @brief Write any message to every gui clients
 * @param clients The cli_t structure
 * @param str The string we want to write
*/
void write_to_graphics_clients(const cli_t clients[MAX_CLIENT],
    const char *str);

/**
 * @brief Write unknown command to ai or gui client.
 * It already check if the client is ai or gui.
 * @param client The cli_t structure
*/
void write_unknown_command(const cli_t client);



//!! FINDER !!

/**
 * @brief Find the value of a parameter in the arg_s structure by his parameter
 * @param arguments The structure where parameters and parameters value
 * are stored
 * @param param The parameter we want to search
 * @return The value of the parameter
*/
void *find_value_by_param(const struct arg_s **arguments, char *param);

/**
 * @brief Find the index where a parameter is in the arg_s structure by
 * his parameter
 * @param arguments The structure where parameters and parameters value
 * are stored
 * @param param The parameter we want to search
 * @return The index where the parameter is in
*/
int find_index_by_param(const struct arg_s **arguments, char *param);



//!! GETTER !!

/**
 * @brief Get array len
 * @param array
 * @return lenght of array or UNDEFINED if array not NULL terminated
 */
size_t get_array_len(char **array);



//!! FREE !!

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
void free_args(struct arg_s **args, const size_t size);

/**
 * @brief Free any ** array up to n
 * @attention if n is superior to the array size the behaviour is undefined
 * @param to_free
 * @param n
 */
void free_array_size_n(void *to_free, const size_t n);



// FILL

/**
 * @brief Refill the map with ressources (use in runtime)
 * @param game_data The structure where game data are stored
*/
void refill_map(game_data_t *game_data);

/**
 * @brief Fill the map with ressources (use in initialization)
 * @param server The general server structure
*/
void fill_map(server_handler_t *server);

/**
 * @brief Fill the 2 dimensions array in the event structure to store
 * ai commands arguments
 * @param src The 2 dimensions array to copy
 * @param index_start The index where to start to copy
 * @param size The size of the source 2 dimensions array
*/
char **fill_arg_in_event(char **src, const int index_start, size_t size);



// CASTER

/**
 * @brief Turn string to char **
 * @param str
 * @param delim
 * @return splited string
 */
char **str_to_word_array(const char *str, const char delim);

/**
 * @brief Turn an array of string into a simple string
 * @param ac number of element in the array
 * @param av Array of string
 * @return concanated string or NULL on error
 */
char *array_to_str(int ac, const char **av);

#endif //SERVER_UTILS_H
