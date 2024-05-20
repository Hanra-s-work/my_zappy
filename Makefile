##
## EPITECH PROJECT, 2023
## my_zappy
## File description:
## Makefile
##

NAME_AI	=	zappy_ai
NAME_GUI	=	zappy_gui
NAME_SERVER	=	zappy_server

DIR_AI	=	./src/ai
DIR_GUI	=	./src/gui_client
DIR_SERVER	=	./src/server

all:	zappy_server zappy_gui	zappy_ai

zappy_ai:
	make -C $(DIR_AI) NAME=$(NAME_AI) all

zappy_gui:
	make -C $(DIR_GUI) NAME=$(NAME_GUI) all

zappy_server:
	make -C $(DIR_SERVER) NAME=$(NAME_SERVER) all

clean: zappy_ai_clean zappy_gui_clean zappy_server_clean

zappy_ai_clean:
	make -C $(DIR_AI) clean

zappy_gui_clean:
	make -C $(DIR_GUI) clean

zappy_server_clean:
	make -C $(DIR_SERVER) clean


fclean: zappy_ai_fclean zappy_gui_fclean zappy_server_fclean

zappy_ai_fclean:
	make -C $(DIR_AI) fclean

zappy_gui_fclean:
	make -C $(DIR_GUI) fclean

zappy_server_fclean:
	make -C $(DIR_SERVER) fclean


re: zappy_ai_re zappy_gui_re zappy_server_re

zappy_ai_re:
	make -C $(DIR_AI) re

zappy_gui_re:
	make -C $(DIR_GUI) re

zappy_server_re:
	make -C $(DIR_SERVER) re


debug: zappy_ai_debug zappy_gui_debug zappy_server_debug

zappy_ai_debug:
	make -C $(DIR_AI) debug

zappy_gui_debug:
	make -C $(DIR_GUI) debug

zappy_server_debug:
	make -C $(DIR_SERVER) debug


tests_run: zappy_ai_tests_run zappy_gui_tests_run zappy_server_tests_run

zappy_ai_tests_run:
	make -C $(DIR_AI) tests_run

zappy_gui_tests_run:
	make -C $(DIR_GUI) tests_run

zappy_server_tests_run:
	make -C $(DIR_SERVER) tests_run


coverage: zappy_ai_coverage zappy_gui_coverage zappy_server_coverage

zappy_ai_coverage:
	make -C $(DIR_AI) coverage

zappy_gui_coverage:
	make -C $(DIR_GUI) coverage

zappy_server_coverage:
	make -C $(DIR_SERVER) coverage

.PHONY:	all zappy_ai zappy_gui zappy_server	\
		clean zappy_ai_clean zappy_gui_clean zappy_server_clean	\
		fclean zappy_ai_fclean zappy_gui_fclean zappy_server_fclean	\
		debug zappy_ai_debug zappy_gui_debug zappy_server_debug	\
		coverage zappy_ai_coverage zappy_gui_coverage zappy_server_coverage	\
		tests_run zappy_ai_tests_run zappy_gui_tests_run zappy_server_tests_run
