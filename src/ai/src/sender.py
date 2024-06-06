##
# EPITECH PROJECT, 2023
# my_zappy
# File description:
# sender.py
##

from threading import Thread
from constants import GlobalVariables
from custom_functions import pinfo,  psuccess, perror, pdebug, pwarning


class SenderThread(Thread):
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
        pinfo(self.constants, "The class Thread sender is initialised")
