##
## EPITECH PROJECT, 2024
## Raytracer
## File description:
## Makefile
##

SRC_MAIN	=	./src/main.c

SRC	=	

CC	=	gcc

RM	=	rm -rf

OBJ	=	$(SRC:.cpp=.o)

OBJ_MAIN	=	$(SRC_MAIN:.cpp=.o)

CFLAGS	=	-Wall -Wextra

CPPFLAGS	=	-iquote ./include

LDLIBS	=	-lsfml

LDFLAGS	=	-L.

NAME	=	zappy_server

NAME_TEST	=	$(NAME)_test

all: 		$(NAME)

$(NAME):		$(OBJ) $(OBJ_MAIN)
	$(CC) $(OBJ_MAIN) $(OBJ) -o $(NAME) $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) $(OBJ_MAIN)
	$(RM) $(OBJ)
	$(RM) *.gcno
	$(RM) *.gcda

fclean: 	clean
	$(RM) $(NAME)
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

.PHONY:	all clean fclean re debug tests_run coverage
