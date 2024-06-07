##
# EPITECH PROJECT, 2023
# my_zappy
# File description:
# logistics.py
##

from threading import Thread
from constants import GlobalVariables
from custom_functions import pinfo,  psuccess, perror, pdebug, pwarning


class Sender:
    """
    Fonctions de base qui ajoute des actions dans la queue d'envoi
    """

    def __init__(self, my_globals: GlobalVariables) -> None:
        self.my_globals = my_globals

    def forward(self) -> None:
        """
        Ajoute la commande "forward" a la queue d'envoi
        """
        self.my_globals.response_buffer.append(
            {self.my_globals.commands.FORWARD: ""}
        )

    def left(self) -> None:
        """
        Ajoute la commande "forward" a la queue d'envoi
        """
        self.my_globals.response_buffer.append(
            {self.my_globals.commands.LEFT: ""}
        )

    def look(self) -> None:
        """
        Ajoute la commande "forward" a la queue d'envoi
        """
        self.my_globals.response_buffer.append(
            {self.my_globals.commands.LOOK: ""}
        )

    def fork(self) -> None:
        """
        Ajoute la commande "forward" a la queue d'envoi
        """
        self.my_globals.response_buffer.append(
            {self.my_globals.commands.FORK: ""}
        )

    def right(self) -> None:
        """
        Ajoute la commande "forward" a la queue d'envoi
        """
        self.my_globals.response_buffer.append(
            {self.my_globals.commands.RIGHT: ""}
        )

    def empty(self) -> None:
        """
        Ajoute la commande "forward" a la queue d'envoi
        """
        self.my_globals.response_buffer.append(
            {self.my_globals.commands.EMPTY: ""}
        )

    def eject(self) -> None:
        """
        Ajoute la commande "forward" a la queue d'envoi
        """
        self.my_globals.response_buffer.append(
            {self.my_globals.commands.EJECT: ""}
        )

    def inventory(self) -> None:
        """
        Ajoute la commande "forward" a la queue d'envoi
        """
        self.my_globals.response_buffer.append(
            {self.my_globals.commands.INVENTORY: ""}
        )

    def connect_nbr(self) -> None:
        """
        Ajoute la commande "forward" a la queue d'envoi
        """
        self.my_globals.response_buffer.append(
            {self.my_globals.commands.CONNECT_NBR: ""}
        )

    def set_obj(self) -> None:
        """
        Ajoute la commande "forward" a la queue d'envoi
        """
        self.my_globals.response_buffer.append(
            {self.my_globals.commands.SET_OBJECT: ""}
        )

    def take_obj(self) -> None:
        """
        Ajoute la commande "forward" a la queue d'envoi
        """
        self.my_globals.response_buffer.append(
            {self.my_globals.commands.TAKE_OBJECT: ""}
        )

    def incantation(self) -> None:
        """
        Ajoute la commande "forward" a la queue d'envoi
        """
        self.my_globals.response_buffer.append(
            {self.my_globals.commands.INCANTATION: ""}
        )

    def broadcast(self) -> None:
        """
        Ajoute la commande "forward" a la queue d'envoi
        """
        self.my_globals.response_buffer.append(
            {self.my_globals.commands.BROADCAST_TEXT: ""}
        )


class LogicsticsThread(Thread):
    """_summary_

    Args:
        Thread (_type_): _description_
    """

    def __init__(self, my_variables: GlobalVariables) -> None:
        """_summary_

        Args:
            my_variables (GlobalVariables): _description_
        """
        super().__init__()
        self.constants = my_variables

    def run(self) -> None:
        """_summary_
        This is the function that is called when a thread is started
        """
        pinfo(self.constants, "The class Thread logistics is initialised")
