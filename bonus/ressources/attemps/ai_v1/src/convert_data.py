##
# EPITECH PROJECT, 2023
# my_zappy
# File description:
# convert_data.py
##

from constants import Commands, Items, TranslationReference


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
        # print(f"data = '{self.data}'")
        self.tr = TranslationReference()
        self.enum_equivalence = self.tr.enum_equivalence
        self.text_equivalence = self.tr.text_equivalence
        self.item_string_to_class = self.tr.item_string_to_class
        self.item_class_to_string = self.tr.item_class_to_string

        self.item_equivalence_input = {
            Commands.LOOK: self._input_parse_look,
            Commands.BROADCAST_TEXT: self._input_parse_inventory
        }

        self.item_equivalence_output = {
            Commands.BROADCAST_TEXT: self._output_parse_inventory
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
        return self.error

    def set_raw_data(self, data: any) -> int:
        """_summary_

        Args:
            data (any): _description_: The type of data is meant to be of type dict or string or a set of byte string.
            Other formats will return an error.
            If the content is empty, an error is returned.

        Returns:
            int: _description_: success if it succeeded to update the raw data, error if it failed to update the raw data.
        """
        return self.update_raw_data(data)

    def _process_inventory(self, data_list: list[str]) -> dict[Commands, list[list[str, int]]]:
        """_summary_
            This function is to be used to process the inventory list.
        Args:
            data_list (list[str]): _description_: The raw list

        Returns:
            dict[Commands, list[str]]: _description_: The converted version
        """
        processed_result = []

        for i in data_list:
            name, quantity = i.split(" ")
            if quantity.isnumeric() is False:
                return {Commands.UNKNOWN: ""}
            processed_result.append([name.strip(), int(quantity)])
        return {Commands.INVENTORY: processed_result}

    def _process_look(self, data: list[str]) -> dict[Commands, list[Items]]:
        """_summary_
        This function is in charge of converting the input to a list of items.

        Args:
            data (list[str]): _description_: The semi processed list based of the input

        Returns:
            dict[Commands, list[Items or str]]: _description_: The final converted version of the input
        """

        processed_result = []
        temporary_result = []
        for i in data:
            if " " in i:
                for j in i.split(" "):
                    temporary_result.append(j)
            else:
                temporary_result.append(i)

        for i in temporary_result:
            tmp = i.strip()
            if tmp in self.item_string_to_class:
                processed_result.append(self.item_string_to_class[tmp])
            else:
                processed_result.append(Items.UNKNOWN)
        return {Commands.LOOK: processed_result}

    def _special_list_treatment(self) -> dict[Commands, any]:
        """_summary_
        Function in charge of the converting a list input to the correct response command.

        Returns:
            dict[Commands, any]: _description_: The converted list
        """
        key = ","
        if key not in self.data:
            return {Commands.BROADCAST_TEXT: self.data}
        data = self.data[1:-1]
        data_list = data.split(key)
        if data_list[-1] == "":
            data_list.pop(-1)
        if len(data_list) == 0:
            return {Commands.LOOK: []}
        if " " in data_list[0] and data_list[0][-1].isnumeric():
            return self._process_inventory(data_list)
        return self._process_look(data)

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
        if "[" in self.data:
            return self._special_list_treatment()
        if len(self.data) == 0:
            return {command: arguments}
        if self.data.lower() in self.enum_equivalence:
            command = self.enum_equivalence[self.data.lower()]
        else:
            command = Commands.BROADCAST_TEXT
            arguments = self.data
        self.data = None
        return {command: arguments}

    def _input_parse_look(self, data: str) -> list[list[str]]:
        """_summary_

        Input data:
            "[tile1, tile2, ...]"
            ex: "[player remedy, ...]"
        Look, command format (output):
            {Command.look:[["player", "food", "Linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"], ...  ]}
                            tile 1                                                                                tile n
        Args:
            data (str): _description_: The arguments provided alongside the command

        Returns:
            list[list[str]]: _description_: The Internal process data
        """
        result = []
        data = data.split(', ')
        if "[" in data[0]:
            data[0] = data[0][1:]
        if "]" in data[-1]:
            data[-1] = data[-1][:-1]
        for i in data:
            print(f"i = {i}")
            term = i.lower()
            if term in self.item_string_to_class:
                term = self.item_string_to_class[term]
            else:
                continue
            result.append(term)

        return result

    def _input_parse_inventory(self, data: str) -> list[dict[Items, int]]:
        """_summary_

        Input data:
            "[linemate n, sibur n, ...]"
            ex: "[linemate 20 sibur 10, ...]"
        Look, command format (output):
            {Command.INVENTORY:[{Items.LINEMATE: 20}, {Items.SIBUR, 10}, ...]}

        Args:
            data (str): _description_: The arguments provided alongside the command

        Returns:
            list[dict[Items, int | str]]: _description_: The Internal process data
        """
        result = []
        data = data.split(', ')

        if "[" in data[0]:
            data[0] = data[0][1:]
        if "]" in data[-1]:
            data[-1] = data[-1][:-1]
        for i in data:
            if " " in i:
                term, definition = i.split(" ", 1)
                term = term.lower()
                if definition.isnumeric():
                    definition = int(definition)
                else:
                    continue
                if term in self.item_string_to_class:
                    term = self.item_string_to_class[term]
                else:
                    continue
                result.append({term: definition})
            else:
                term = i.lower()
                if term in self.item_string_to_class:
                    term = self.item_string_to_class[term]
                else:
                    continue
                result.append({term: definition})

        return result

    def _output_parse_inventory(self, data: list[dict[Items, int]]) -> str:
        """_summary_

        Input data:
            {Command.INVENTORY:[{Items.LINEMATE: 20}, {Items.SIBUR, 10}, ...]}
        Look, command format (output):
            "[linemate n, sibur n, ...]"
            ex: "[linemate 20 sibur 10, ...]"

        Args:
            data (str): _description_: The arguments provided alongside the command

        Returns:
            list[dict[Items, int]]: _description_: The Internal process data
        """
        result = "["
        nodes = []
        for i in data:
            term = list(i)[0]
            definition = i[term]
            tmp = term + " " + definition
            nodes.append(tmp)
        result += ", ".join(nodes) + "]" + "\n"
        return result

    def to_external(self) -> str:
        """_summary_
        Convert the internal data to the external language used by the over programs

        Returns:
            str: _description_: a string containing the command for the other programs
        """
        result_order = ""
        if isinstance(self.data, dict) is False:
            if isinstance(self.data, str):
                if self.data == "":
                    self.data += "\n"
                if self.data[-1] != '\n':
                    self.data += '\n'
                return self.data
            return (self.text_equivalence[Commands.UNKNOWN] + '\n')
        if len(self.data) == 0:
            return (self.text_equivalence[Commands.UNKNOWN] + '\n')
        command = list(self.data)[0]
        arguments = self.data[command]
        if command == Commands.UNKNOWN:
            return (self.text_equivalence[Commands.UNKNOWN] + '\n')
        if command in self.text_equivalence:
            result_order = self.text_equivalence[command]
        if arguments == "":
            result_order += '\n'
            return result_order
        if command in self.item_equivalence_output:
            arguments = self.item_equivalence_output[command](arguments)
        else:
            if isinstance(arguments, list) is True:
                result_order += " ".join(arguments)
            else:
                result_order += " " + str(arguments)
        result_order += '\n'
        self.data = None
        return result_order
