##
# EPITECH PROJECT, 2023
# my_zappy
# File description:
# convert_data.py
##

from constants import GlobalVariables, Commands


class ConvertData:
    """_summary_
    Class in charge of converting and translating the data received from the outside into commands understood by the internal program
    """

    def __init__(self, data):
        self.data = data

    def to_internal(self) -> dict[Commands, any]:
        """_summary_
        Convert the raw data to the internal language used by the ai

        Returns:
            dict[Commands, any]: _description_: the format of a node of data comming back
        """
        return {"": ""}

    def to_external(self) -> str:
        """_summary_
        Convert the internal data to the external language used by the over programs

        Returns:
            str: _description_: a string containing the command for the other programs
        """
        return ""
