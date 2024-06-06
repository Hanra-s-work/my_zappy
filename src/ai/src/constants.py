##
# EPITECH PROJECT, 2023
# my_zappy
# File description:
# constants.py
##

"""
    _summary_
    This file (constants.py) is in charge of storing any variable that needs to be shared to different classes and not just be a copy
"""


class Commands:
    """ 
    _sumary_
    This is a python version of an enum.
    This enum hosts a set of variables referencing the available commands for the exchange between the ai and the server
    """
    LEFT: int = 1
    LOOK: int = 2
    FORK: int = 3
    RIGHT: int = 4
    EJECT: int = 5
    EMPTY: int = 6
    FORWARD: int = 7
    INVENTORY: int = 8
    CONNECT_NBR: int = 9
    SET_OBJECT: int = 10
    TAKE_OBJECT: int = 11
    INCANTATION: int = 12
    BROADCAST_TEXT: int = 13


class Items:
    """
    _summary_
    This is a python version of an enum.
    This enum hosts a set of variables referencing the available types of objects that can be gathered from the field
    """
    FOOD = 1
    LINEMATE = 2
    DERAUMERE = 3
    SIBUR = 4
    MENDIANE = 5
    PHIRAS = 6
    THYSTAME = 7


class ServerData:
    """
    _summary_
    This is the class in charge of storing data referring the information that the server needs in order to function
    """

    def __init__(self, ip: str = "0.0.0.0", port: int = 8080) -> None:
        self.ip: str = ip
        self.port: int = port
        self.raw_buffer: list[dict[Commands, any]] = []
        self.client_address: list[any] = []


class RequestData:
    """
    _summary_
    This is the class in charge of storing the data referring to the data that needs to be sent out to the server
    """

    def __init__(self, ip: str = "0.0.0.0", port: int = 8080) -> None:
        self.ip: str = ip
        self.port: int = port
        self.response_buffer: list[list[dict[Commands, any]]] = []


class AI:
    """
    _sumary_
    This is the class in charge of hosting the global variables that will be accessed by the ai section of the program
    """

    def __init__(self) -> None:
        self.items: Items = Items()
        self.nb_items: int = 0
        self.current_items: list[any] = []


class GlobalVariables:
    """ This is the class in charge of storing the variables that are to be globally synced throughout the program"""

    def __init__(self, success: int = 0, error: int = 84, ip: str = "0.0.0.0", port: int = 8080) -> None:
        self.ai: AI = AI()
        self.items: Items = Items()
        self.error: int = error
        self.success: int = success
        self.commands: Commands = Commands()
        self.server_data: ServerData = ServerData(ip="0.0.0.0", port=port)
        self.current_status: int = self.success
        self.request_data: RequestData = RequestData(ip=ip, port=port)
        self.current_buffer: list[dict[Commands, any]] = []
        self.created_threads: dict[str, any] = {}
        self.continue_running: bool = True
