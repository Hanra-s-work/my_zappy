##
## EPITECH PROJECT, 2024
## Raytracer
## File description:
## Makefile
##

SRC_MAIN	=	./src/main.cpp

SRC	=	./src/sub_main.cpp	\
		./src/ArgumentHandling.cpp	\
		./src/Parsing.cpp	\
		./src/Graphic.cpp	\
		./src/Player.cpp	\
		./src/NetworkClient.cpp	\
		./src/Game.cpp

CXX	=	g++

RM	=	rm -rf

OBJ	=	$(SRC:.cpp=.o)

OBJ_MAIN	=	$(SRC_MAIN:.cpp=.o)

CXXFLAGS	=	 -Wall -Wextra

THREAD_FLAGS	=	-pthread

CPPFLAGS	=	-iquote ./include

LDLIBS	=	-lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network

LDFLAGS	=	-L.

NAME	=	zappy_gui

NAME_TEST	=	$(NAME)_test

all: 		$(NAME) update_binary_location

$(NAME):		$(OBJ) $(OBJ_MAIN)
	$(CXX) $(OBJ_MAIN) $(OBJ) -o $(NAME) $(LDFLAGS) $(LDLIBS)

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
