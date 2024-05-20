##
## EPITECH PROJECT, 2024
## Raytracer
## File description:
## Makefile
##

SRC_MAIN	=	./src/main.py

NAME	=	zappy_ai

NAME_TEST	=	$(NAME)_test

all: 		$(NAME)

$(NAME):		$(OBJ) $(OBJ_MAIN)
	$(CXX) $(OBJ_MAIN) $(OBJ) -o $(NAME) $(LDFLAGS) $(LDLIBS)

clean:
	$(RM) $(OBJ_MAIN)
	$(RM) $(OBJ)
	$(RM) *.gcno
	$(RM) *.gcda

fclean: 	clean
	$(RM) $(NAME)

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
