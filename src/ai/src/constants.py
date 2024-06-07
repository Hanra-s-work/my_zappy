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

from sys import stderr
from display_tty import Disp, TOML_CONF
from colourise_output import ColouriseOutput


# These define the maximum and minimum port ranges for the tcp protocol
MAX_PORT_RANGE = 9000
MIN_PORT_RANGE = 1024

# Thread kill delay
THREAD_TIMEOUT = 5  # None

# Disabeling animation
TOML_CONF['PRETTIFY_OUTPUT'] = False


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
    UNKNOWN: int = 14


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
        self.make_udp_wait: bool = False
        self.buffer_size: int = 1024*4
        self.startup_message: str = f"AI land is live at {self.ip}:{self.port}"
        self.welcome_message: str = "Welcome to AI land."
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


class AI:
    """
    _sumary_
    This is the class in charge of hosting the global variables that will be accessed by the ai section of the program
    """

    def __init__(self) -> None:
        self.items: Items = Items()
        self.nb_items: int = 0
        self.current_items: list[any] = []


class MessageColours:
    """
    _summary_
    This is the class in charge of storing the different colours that will be used for the messages
    """
    END = 'rr'
    INFO = '0B'
    ERROR = '0C'
    DEBUG = '0D'
    SUCCESS = '0A'
    WARNING = '0E'
    DEFAULT = "0F"


class UserArguments:
    """
    _summary_
    This is the class in charge of storing the arguments passed by the user
    """

    def __init__(self, ip: str = "0.0.0.0", port: int = 8080, name: str = "No name", debug: bool = False) -> None:
        self.host: str = ip
        self.port: int = port
        self.name: str = name
        self.debug: bool = debug


class GlobalVariables:
    """
    _summary_
    This is the class in charge of storing the variables that are to be globally synced throughout the program

    Args:
        success (int, optional): _description_. Defaults to 0.
        error (int, optional): _description_. Defaults to 84.
        ip (str, optional): _description_. Defaults to "0.0.0.0".
        port (int, optional): _description_. Defaults to 8080.
        name (str, optional): _description_. Defaults to "".
    """

    def __init__(self, success: int = 0, error: int = 84, ip: str = "0.0.0.0", port: int = 8080, name: str = "", debug: bool = False) -> None:
        # Heartbeat variable, if it is set to false, the program stops
        self.continue_running: bool = True

        # Classes acting as enums
        self.items: Items = Items()
        self.commands: Commands = Commands()

        # Bundle of variables relevant to the sections of the program containing the same name
        self.ai: AI = AI()
        self.server_data: ServerData = ServerData(ip="0.0.0.0", port=port)
        self.request_data: RequestData = RequestData(ip=ip, port=port)
        self.user_arguments = UserArguments(ip, port, name, debug)

        # Variable in charge of tracking the threads that were created
        self.created_threads: dict[str, any] = {}

        # Status tracking
        self.error: int = error
        self.success: int = success
        self.current_status: int = self.success

        # The converted income from the server
        self.current_buffer: list[dict[Commands, any]] = []
        self.response_buffer: list[list[dict[Commands, any]]] = []

        # Message customisation desing
        self.message_colours: MessageColours = MessageColours()
        self.colourise_output: ColouriseOutput = ColouriseOutput()
        self.beautify_error: Disp = Disp(
            toml_content=TOML_CONF,
            save_to_file=True,
            file_name="",
            file_descriptor=stderr
        )
        self.beautify_standard: Disp = Disp(
            toml_content=TOML_CONF,
            save_to_file=False
        )
