##
## EPITECH PROJECT, 2024
## Raytracer
## File description:
## Makefile
##

SRC_MAIN	=	./src/main.c

SRC	=	./src/utils/utils.c						\
		./src/utils/array_utils.c				\
		./src/utils/array_to_str.c				\
\
		./src/sub_main.c						\
\
		./src/parsing/arg_parse.c				\
		./src/parsing/check_arg_mandatory.c		\
		./src/parsing/check_arg_value.c			\
		./src/parsing/check_values_validity.c 	\
		./src/parsing/command_parse.c			\

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
