##
## EPITECH PROJECT, 2024
## Raytracer
## File description:
## Makefile
##

SRC_MAIN	=	./src/main.c

SRC	=	./src/sub_main.c								\
\
		./src/utils/finder.c							\
		./src/utils/free.c								\
		./src/utils/writer.c							\
		./src/utils/fill.c								\
		./src/utils/array_utils.c						\
		./src/utils/array_to_str.c						\
\
		./src/parsing/arg_parse.c						\
		./src/parsing/check_arg_mandatory.c				\
		./src/parsing/parameter_utils.c					\
		./src/parsing/check_values_validity.c 			\
		./src/parsing/command_parse.c					\
\
		./src/server/server_initialization.c			\
		./src/server/game_data_initialization.c			\
		./src/server/client_management.c 				\
		./src/server/server_loop.c						\
		./src/server/command_handling.c					\
		./src/server/check_event.c						\
\
		./src/commands/map_content.c					\
		./src/commands/player_info.c					\
		./src/commands/sbp.c							\
		./src/commands/tile_content.c					\
\
		./src/commands/gui/zappy_info.c					\
\
		./src/commands/ai_event/event_utils.c			\
		./src/commands/ai_event/broadcast_handler.c		\
		./src/commands/ai_event/connect_handler.c		\
		./src/commands/ai_event/eject_handler.c			\
		./src/commands/ai_event/fork_handler.c			\
		./src/commands/ai_event/forward_handler.c		\
		./src/commands/ai_event/incantation_handler.c	\
		./src/commands/ai_event/incantation_sender.c	\
		./src/commands/ai_event/inventory_handler.c		\
		./src/commands/ai_event/left_handler.c			\
		./src/commands/ai_event/right_handler.c			\
		./src/commands/ai_event/set_handler.c			\
		./src/commands/ai_event/take_handler.c			\
		./src/commands/ai_event/look_handler.c			\
\
		./src/show/show_game_data.c						\

SRC_TEST	=	./tests/arg_parser_test.c

CC	=	gcc

RM	=	rm -rf

OBJ	=	$(SRC:.c=.o)

OBJ_TEST	=	$(SRC_TEST:.c=.o)

OBJ_MAIN	=	$(SRC_MAIN:.c=.o)

CFLAGS	=	-Wall -Wextra

CPPFLAGS	=	-iquote ./include

TESTFLAGS	=	--coverage -lcriterion

NAME	=	zappy_server

NAME_TEST	=	$(NAME)_test

all: 		$(NAME) update_binary_location

$(NAME):		$(OBJ) $(OBJ_MAIN)
	$(CC) $(OBJ_MAIN) $(OBJ) -o $(NAME)

update_binary_location:
	cp -vf $(NAME) ../../$(NAME)

clean:
	$(RM) $(OBJ_MAIN)
	$(RM) $(OBJ)
	$(RM) $(OBJ_TEST)
	$(RM) *.gcno
	$(RM) *.gcda

fclean: 	clean
	$(RM) $(NAME)
	$(RM) ../../$(NAME)
	$(RM) $(NAME_TEST)

re:	fclean all

debug:	CFLAGS += -g3
debug:	clean all

tests_run:
	$(CC) $(SRC) $(SRC_TEST) -o $(NAME_TEST) $(TESTFLAGS) $(CFLAGS) $(CPPFLAGS)
	./$(NAME_TEST)

coverage:	tests_run
	gcovr --exclude ./tests
	gcovr --exclude ./tests --branches

.PHONY:	all clean fclean re debug tests_run coverage update_binary_location
