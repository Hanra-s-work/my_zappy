##
# EPITECH PROJECT, 2023
# my_zappy [fed34_prox_vm]
# File description:
# logistics_thread.py
##

import sys
from datetime import datetime

from convert_data import ConvertData
from global_variables import GlobalVariables, Commands, Items
from custom_functions import pinfo,  psuccess, perror, pdebug, pwarning


class Logistics:
    """_summary_
    This is the class in charge of containing the ai which provides a purpose for this program

    Args:
        Thread (_type_): _description_: The class that is to be used in order to start threads
    """

    def __init__(self, global_variables: GlobalVariables) -> None:
        self.global_variables = global_variables
        self.global_variables.ai_status = self.global_variables.success
        self.client_number = ""
        self.client_coordinates = ()
        self.welcome_received = False
        self.client_number_received: bool = False
        self.initialisation_complete = False
        self.global_variables.ai_ready = True
        self.nb_responses = 0
        self.tile_content = []
        self.random_seed = self._create_random_seed()
        self.evolution_level = 1
        self.stall = False
        self.direction_options_list = ["forward", "left", "right"]
        self.direction_options = {
            "forward": self._forward,
            "left": self._left,
            "right": self._right
        }

    def _create_random_seed(self) -> int:
        """_summary_
        Generate a random seed
        Returns:
            int: _description_
        """
        c_time = datetime.now()
        final_seed = c_time.hour + c_time.minute + c_time.second + c_time.microsecond
        pinfo(self.global_variables, f"Generated seed: {final_seed}")
        return final_seed

    def _forward(self) -> None:
        """_summary_
            Add the forward command
        """
        e = ConvertData(
            data=self.global_variables.translation_reference.text_equivalence[Commands.FORWARD],
            error=self.global_variables.error,
            success=self.global_variables.success
        )
        output = e.to_external()
        pinfo(self.global_variables, f"Command sent: {output}")
        self.global_variables.response_buffer.append(output)

    def _left(self) -> None:
        """_summary_
            Add the left command
        """
        e = ConvertData(
            data=self.global_variables.translation_reference.text_equivalence[Commands.LEFT],
            error=self.global_variables.error,
            success=self.global_variables.success
        )
        output = e.to_external()
        pinfo(self.global_variables, f"Command sent: {output}")
        self.global_variables.response_buffer.append(output)

    def _right(self) -> None:
        """_summary_
            Add the right command
        """
        e = ConvertData(
            data=self.global_variables.translation_reference.text_equivalence[Commands.RIGHT],
            error=self.global_variables.error,
            success=self.global_variables.success
        )
        output = e.to_external()
        pinfo(self.global_variables, f"Command sent: {output}")
        self.global_variables.response_buffer.append(output)

    def _my_randint(self, minimum: int = 0, maximum: int = 3) -> int:
        """_summary_
            This is a function that will be used in order to provide a randome number without using the random library.
        """
        artificial_turn = 200
        counter = 0
        while counter < artificial_turn:
            pdebug(self.global_variables, "(logistics) In random")
            c_time = datetime.now()
            current_time = c_time.hour + c_time.minute + c_time.second + c_time.microsecond
            final_number = (current_time + self.random_seed) % (maximum + 1)
            if minimum <= final_number <= maximum:
                return final_number
            counter += 1
        return minimum

    def _change_my_mind(self) -> None:
        """_summary_
        This function is the one in charge of creating a random movement
        """
        move = self._my_randint(0, len(self.direction_options) - 1)
        pinfo(
            self.global_variables,
            f"Selected direction: {self.direction_options_list[move]}"
        )
        self.direction_options[self.direction_options_list[move]]()

    def _update_ai_status(self, status: int) -> None:
        """_summary_
            This function works like a onetime valve, if one error ever gets raised, the variable will never go back to 0.
        Args:
            status (int): _description_: the run status of the previous function
        """
        if status != self.global_variables.success:
            pwarning(
                self.global_variables,
                f"The global status if not a success, error code: {status}"
            )
            self.global_variables.ai_status = status
        psuccess(self.global_variables, "The global status is a success.")

    def _process_welcome(self, data: str) -> int:
        """_summary_
            This function will set the variables corresponding to the initialisation process
        Returns:
            int: _description_: The processing status
        """
        if "WELCOME" in data:
            pinfo(
                self.global_variables,
                "Welcome key received"
            )
            self.global_variables.response_buffer.append(
                self.global_variables.user_arguments.name
            )
            self.welcome_received = True
            return self.global_variables.success
        pdebug(
            self.global_variables,
            f"(logistics): response = {data}, nb_responses = {self.nb_responses}"
        )
        self._exit_error("Did not receive the expected welcome message")
        return self.global_variables.error

    def _process_client_number(self, data: str) -> int:
        """_summary_
            This function will check if we have received the client number
        Args:
            data (str): _description_: The incoming data

        Returns:
            int: _description_: The status of the processed data
        """
        if data in ({}, []):
            response = f"Client number cannot be empty.\nYou entered:'{data}'"
            perror(self.global_variables, response)
            return self._exit_error(f"Error: {response}")
        if isinstance(data, (dict)):
            data = data[list(data)[0]]
        if isinstance(data, list):
            data = data[0]
        if data.isnumeric():
            self.client_number = int(data)
            self.client_number_received = True
        return self.global_variables.success

    def _process_map_dimensions(self, data: str) -> int:
        """_summary_
            This is a function that will make sure that the dimensions of the map.
        Args:
            data (str): _description_

        Returns:
            int: _description_
        """
        if " " not in data:
            response = f"Map dimensions cannot be empty.\nYou entered:'{data}'"
            perror(self.global_variables, response)
            return self._exit_error(f"Error: {response}")
        dimensions = data.split(" ")
        if len(dimensions) > 0 and dimensions[0] == '':
            dimensions.pop(0)
        if len(dimensions) > 0 and dimensions[-1] == '':
            dimensions.pop(-1)
        if len(dimensions) == 2:
            if dimensions[0].isnumeric() and dimensions[1].isnumeric():
                self.client_coordinates = (
                    int(dimensions[0]), int(dimensions[1]))
                pdebug(
                    self.global_variables,
                    f"Client coordinates = {self.client_coordinates}"
                )
                self.initialisation_complete = True
                self.global_variables.ai_ready = True
                self._append_look_command()
                return self.global_variables.success
        response = f"Map dimensions cannot be empty.\nYou entered:'{data}'"
        perror(self.global_variables, response)
        return self._exit_error(f"Error: {response}")

    def _can_evolve(self, command: str) -> bool:
        """_summary_
            This function checks if the ai can evolve.
        Args:
            command (str | list): _description_: The content of the Look response

        Returns:
            bool: _description_: Returns True if the ai can get to the next level, otherwise False is returned.
        """
        max_i = len(command)
        pdebug(
            self.global_variables,
            f"(logistic) _can_evolve: max_i = {max_i}, Provided command = {command}"
        )
        if max_i == 0:
            pdebug(
                self.global_variables,
                "(logistics) _can_evolve: The command is empty"
            )
            return False
        if self.evolution_level > 1:
            return True
        if Items.LINEMATE in command or "linemate" in command or "Linemate" in command:
            psuccess(
                self.global_variables,
                "The item Linemate was found on the ground"
            )
            return True
        pdebug(
            self.global_variables,
            "(logistics) _can_evolve: The Linemate item is not found"
        )
        return False

    def _exit_error(self, string: str) -> int:
        """_summary_
            This function should never be triggered in a normal use case.
            This function will send an error message and set the global status to self.global_variable.error
        Returns:
            int: _description_: The error status defined in global_variables
        """
        self.global_variables.continue_running = False
        status = self.global_variables.error
        self._update_ai_status(status)
        self.global_variables.response_buffer.append(f"Error: {string}\n")
        return status

    def _append_look_command(self) -> None:
        """_summary_
            This function appends the look command to the response buffer.
        """
        e = ConvertData(
            data=self.global_variables.translation_reference.text_equivalence[Commands.LOOK],
            error=self.global_variables.error,
            success=self.global_variables.success
        )
        output = e.to_external()
        pinfo(self.global_variables, f"Command sent: {output}")
        self.global_variables.response_buffer.append(output)

    def _to_human_readable(self, code: int) -> str:
        """_summary_
            Replace the code with the corresponding state.
        Args:
            code (int): _description_: The corresponding code

        Returns:
            str: _description_: The corresponding text that the human can understand
        """
        if code in self.global_variables.translation_reference.text_equivalence:
            return self.global_variables.translation_reference.text_equivalence[code]
        return code

    def _calculate_next_move(self, response: dict[Commands, any]) -> int:
        """_summary_
            This function will calculate the next move based on the response from the server.

        Args:
            response (dict[Commands, any]): _description_: The query that came in from the tcp protocol.

        Returns:
            int: _description_: The status of the execution.
        """
        status = self.global_variables.success

        pdebug(self.global_variables, f"Incoming response =  {response}")

        if Commands.MESSAGE in response:
            pinfo(
                self.global_variables,
                f"Received message: {response[Commands.MESSAGE]}"
            )
            return status

        node = list(response)[0]
        if self.stall is True and isinstance(response[node], str) is True and "Current level:" in response:
            self.stall = False
            data: list[str] = response[node].split(" ")
            while '' == data[-1]:
                data.pop(-1)
            if data[-1].isnumeric():
                level = int(data[-1])
                if self.evolution_level + 1 == level:
                    self.evolution_level += 1
                else:
                    self.evolution_level = level

        if Commands.INCANTATION in response and response[Commands.INCANTATION].lower() == "ko" and self.evolution_level > 1:
            self._change_my_mind()

        if response[list(response)[0]] in ("ko", "KO", "Ko", "kO"):
            perror(
                self.global_variables,
                f"Command = '{self._to_human_readable(list(response)[0])}' failed"
            )
            self._append_look_command()
            return self.global_variables.success

        if Commands.LOOK in response:
            psuccess(self.global_variables, f"Look response = {response}")
            self.tile_content = response[Commands.LOOK]
            if self._can_evolve(response[Commands.LOOK]) is True:
                e = ConvertData(
                    data=self.global_variables.translation_reference.text_equivalence[
                        Commands.INCANTATION
                    ],
                    error=self.global_variables.error,
                    success=self.global_variables.success
                )
                self.global_variables.response_buffer.append(e.to_external())
            else:
                self._change_my_mind()

        elif Commands.LEFT in response and response[Commands.LEFT].lower() == "ok":
            self._append_look_command()

        elif Commands.RIGHT in response and response[Commands.RIGHT].lower() == "ok":
            self._append_look_command()

        elif Commands.FORWARD in response and response[Commands.FORWARD].lower() == "ok":
            self._append_look_command()

        elif Commands.INCANTATION in response and response[Commands.INCANTATION] == "Elevation underway":
            self.stall = True

        else:
            self._append_look_command()

        return status

    def dispatcher(self, response: dict[Commands, any]) -> int:
        """_summary_

        Args:
            response (str): _description_: The converted response

        Returns:
            int: _description_: The status response of the program
        """
        status = self.global_variables.success
        self.nb_responses += 1
        pinfo(self.global_variables, f"data = {response}")

        if Commands.UNKNOWN in response and self.nb_responses == 1:
            status = self._process_welcome(response[Commands.UNKNOWN])
        elif Commands.UNKNOWN in response and self.welcome_received is True and self.nb_responses == 2:
            status = self._process_client_number(response)
        elif Commands.UNKNOWN in response and self.client_number_received is True and self.nb_responses == 3:
            status = self._process_map_dimensions(response[Commands.UNKNOWN])
        elif self.nb_responses >= 4 and self.initialisation_complete is True:
            status = self._calculate_next_move(response)

        self._update_ai_status(status)
        return status


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
