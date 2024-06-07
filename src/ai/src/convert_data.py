##
# EPITECH PROJECT, 2023
# my_zappy
# File description:
# convert_data.py
##

from constants import Commands


class ConvertData:
    """_summary_
    Class in charge of converting and translating the data received from the outside into commands understood by the internal program
    """

    def __init__(self, data, error: int = 84, success: int = 0) -> None:
        self.error = error
        self.success = success
        self.data = data
        if isinstance(data, bytes):
            self.data = data.decode()
        print(f"data = '{self.data}'")
        self.enum_equivalence = {
            "forward": Commands.FORWARD,
            "right": Commands.RIGHT,
            "left": Commands.LEFT,
            "look": Commands.LOOK,
            "inventory": Commands.INVENTORY,
            "broadcast": Commands.BROADCAST_TEXT,
            "connect_nbr": Commands.CONNECT_NBR,
            "fork": Commands.FORK,
            "eject": Commands.EJECT,
            "take": Commands.TAKE_OBJECT,
            "set": Commands.SET_OBJECT,
            "incantation": Commands.INCANTATION,
        }
        self.text_equivalence = {
            Commands.FORWARD: "forward",
            Commands.RIGHT: "right",
            Commands.LEFT: "left",
            Commands.LOOK: "look",
            Commands.INVENTORY: "inventory",
            Commands.BROADCAST_TEXT: "broadcast",
            Commands.CONNECT_NBR: "connect_nbr",
            Commands.FORK: "fork",
            Commands.EJECT: "eject",
            Commands.TAKE_OBJECT: "take",
            Commands.SET_OBJECT: "set",
            Commands.INCANTATION: "incantation",
            Commands.UNKNOWN: "none"
        }

    def update_raw_data(self, data: any) -> int:
        """_summary_

        Args:
            data (any): _description_: The type of data is meant to be of type dict or string or a set of byte string.
            Other formats will return an error.
            If the content is empty, an error is returned.

        Returns:
            int: _description_: success if it succeeded to update the raw data, error if it failed to update the raw data.
        """
        if isinstance(data, (str, dict, bytes)) is True:
            if isinstance(data, bytes):
                data = data.decode()
            if data in ("", {}):
                return self.error
            self.data = data
            return self.success
        else:
            return self.error

    def to_internal(self) -> dict[Commands, any]:
        """_summary_
        Convert the raw data to the internal language used by the ai

        Returns:
            dict[Commands, any]: _description_: the format of a node of data comming back
        """
        command = Commands.UNKNOWN
        arguments = ""
        if isinstance(self.data, str) is False:
            return {command: arguments}
        data_list = self.data.split(" ")
        if len(data_list) == 0:
            return {command: arguments}
        if data_list[-1] == '':
            data_list.pop()
        if len(data_list) == 0:
            return {command: arguments}
        if data_list[0].lower() in self.enum_equivalence:
            command = self.enum_equivalence[data_list[0].lower()]
        if len(data_list) > 1:
            arguments = data_list[1:]
        self.data = None
        return {command: arguments}

    def to_external(self) -> str:
        """_summary_
        Convert the internal data to the external language used by the over programs

        Returns:
            str: _description_: a string containing the command for the other programs
        """
        result_order = ""
        if isinstance(self.data, dict) is False:
            return self.text_equivalence[Commands.UNKNOWN]
        if len(self.data) == 0:
            return self.text_equivalence[Commands.UNKNOWN]
        command, arguments = self.data.keys()
        if command == Commands.UNKNOWN:
            return self.text_equivalence[Commands.UNKNOWN]
        if command.lower() in self.text_equivalence:
            result_order = self.text_equivalence[command]
        if arguments == "":
            return result_order
        if isinstance(arguments, list) is True:
            for i in arguments:
                result_order += " " + str(i)
        else:
            result_order += " " + str(arguments)
        self.data = None
        return result_order
