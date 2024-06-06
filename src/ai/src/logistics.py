##
# EPITECH PROJECT, 2023
# my_zappy
# File description:
# logistics.py
##

from constants import GlobalVariables


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
        self.my_globals.server_data.raw_buffer.append(
            {self.my_globals.commands.FORWARD: ""}
        )

    def left(self) -> None:
        """
        Ajoute la commande "forward" a la queue d'envoi
        """
        self.my_globals.server_data.raw_buffer.append(
            {self.my_globals.commands.LEFT: ""}
        )

    def look(self) -> None:
        """
        Ajoute la commande "forward" a la queue d'envoi
        """
        self.my_globals.server_data.raw_buffer.append(
            {self.my_globals.commands.LOOK: ""}
        )

    def fork(self) -> None:
        """
        Ajoute la commande "forward" a la queue d'envoi
        """
        self.my_globals.server_data.raw_buffer.append(
            {self.my_globals.commands.FORK: ""}
        )

    def right(self) -> None:
        """
        Ajoute la commande "forward" a la queue d'envoi
        """
        self.my_globals.server_data.raw_buffer.append(
            {self.my_globals.commands.RIGHT: ""}
        )

    def empty(self) -> None:
        """
        Ajoute la commande "forward" a la queue d'envoi
        """
        self.my_globals.server_data.raw_buffer.append(
            {self.my_globals.commands.EMPTY: ""}
        )

    def eject(self) -> None:
        """
        Ajoute la commande "forward" a la queue d'envoi
        """
        self.my_globals.server_data.raw_buffer.append(
            {self.my_globals.commands.EJECT: ""}
        )

    def inventory(self) -> None:
        """
        Ajoute la commande "forward" a la queue d'envoi
        """
        self.my_globals.server_data.raw_buffer.append(
            {self.my_globals.commands.INVENTORY: ""}
        )

    def connect_nbr(self) -> None:
        """
        Ajoute la commande "forward" a la queue d'envoi
        """
        self.my_globals.server_data.raw_buffer.append(
            {self.my_globals.commands.CONNECT_NBR: ""}
        )

    def set_obj(self) -> None:
        """
        Ajoute la commande "forward" a la queue d'envoi
        """
        self.my_globals.server_data.raw_buffer.append(
            {self.my_globals.commands.SET_OBJECT: ""}
        )
