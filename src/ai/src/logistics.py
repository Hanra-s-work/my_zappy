##
# EPITECH PROJECT, 2023
# my_zappy [fed34_prox_vm]
# File description:
# logistics_thread.py
##

import sys

from convert_data import ConvertData
from global_variables import GlobalVariables
from custom_functions import pinfo,  psuccess, perror, pdebug, pwarning


class Logistics:
    """_summary_
    This is the class in charge of containing the ai which provides a purpose for this program

    Args:
        Thread (_type_): _description_: The class that is to be used in order to start threads
    """

    def __init__(self, global_variables: GlobalVariables) -> None:
        self.global_variables = global_variables

    def run(self) -> None:
        """_summary_
        This is the function in charge of starting any function that contains the code we wish to run inside the thread we started.
        """
        pinfo(self.global_variables, "Logistics thread started")


if __name__ == "__main__":
    print("This script is not meant to be run as main.")
    NAME = "my_zappy"
    IP = "0.0.0.0"
    PORT = 4242
    ERROR = 84
    SUCCESS = 0
    CLIENT_NUM = 1
    MAP_X = 20
    MAP_Y = 20
    ASCEND = "ASCEND"
    LEFT = "LEFT"
    RIGHT = "RIGHT"
    FORWARD = "FORWARD"
    LIFE_LENGTH = 200
    LIFE_INDEX = 0
    GI = GlobalVariables(
        success=0,
        error=84,
        ip="0.0.0.0",
        port=4242,
        name="my_zappy",
        debug=True
    )
    GI.current_buffer.append(ConvertData("WELCOME").to_internal())
    LI = Logistics(GI)
    LI.start()
    GI.colourise_output.init_pallet()
    GI.colourise_error.init_pallet()
    while GI.continue_running is True:
        if len(GI.sender_data) == 0:
            continue
        if GI.response_buffer[0] == NAME:
            GI.current_buffer.append(
                ConvertData(f"{CLIENT_NUM}\n").to_internal()
            )
            GI.current_buffer.append(
                ConvertData(f" {MAP_X} {MAP_Y}\n").to_external()
            )
        if GI.response_buffer[0] == FORWARD:
            GI.current_buffer.append(ConvertData("ok\n").to_internal())
        if GI.response_buffer[0] == LEFT:
            GI.current_buffer.append(ConvertData("ok\n").to_internal())
        if GI.response_buffer[0] == RIGHT:
            GI.current_buffer.append(ConvertData("ok\n").to_internal())
        if LIFE_INDEX == LIFE_LENGTH:
            GI.current_buffer.append(ConvertData("Dead").to_internal())
        LIFE_INDEX += 1
    pinfo(GI, f"Program stopped with status: {GI.current_status}")
    GI.colourise_output.unload_ressources()
    sys.exit(GI.current_status)
