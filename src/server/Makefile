##
## EPITECH PROJECT, 2024
## Raytracer
## File description:
## Makefile
##

SRC_MAIN	=	./src/main.c

SRC	=	./src/sub_main.c

CC	=	gcc

RM	=	rm -rf

OBJ	=	$(SRC:.c=.o)

OBJ_MAIN	=	$(SRC_MAIN:.c=.o)

CFLAGS	=	-Wall -Wextra

CPPFLAGS	=	-iquote ./include

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
	$(RM) *.gcno
	$(RM) *.gcda

fclean: 	clean
	$(RM) $(NAME)
	$(RM) ../../$(NAME)
	$(RM) $(NAME_TEST)

re:	fclean all

debug:	CFLAGS += -g3
debug:	clean all

tests_run:	LDLIBS	+=	-lcriterion
tests_run:	CXXFLAGS	+=	-coverage
tests_run:	clean
tests_run:	$(NAME_TEST)

$(NAME_TEST):
	$(CXX) $(SRC) -o $(NAME_TEST) $(LDFLAGS) $(LDLIBS)
	./$(NAME_TEST)

coverage:	tests_run
	gcovr --exclude ./tests
	gcovr --exclude ./tests --branches

.PHONY:	all clean fclean re debug tests_run coverage update_binary_location
