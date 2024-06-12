##
# EPITECH PROJECT, 2023
# my_zappy
# File description:
# logistics.py
##

import sys
from time import sleep
from threading import Thread
from datetime import datetime
from constants import Commands, GlobalVariables, Items
from custom_functions import pinfo,  psuccess, perror, pdebug, pwarning


class Sender:
    """
    Basic functions that add actions to the send queue
    """

    def __init__(self, my_globals: GlobalVariables) -> None:
        self.my_globals = my_globals

    def forward(self) -> None:
        """
        Adds the "forward" command to the send queue
        """
        self.my_globals.response_buffer.append(
            {self.my_globals.commands.FORWARD: ""}
        )

    def left(self) -> None:
        """
        Adds the "left" command to the send queue
        """
        self.my_globals.response_buffer.append(
            {self.my_globals.commands.LEFT: ""}
        )

    def look(self) -> None:
        """
        Adds the "look" command to the send queue
        """
        self.my_globals.response_buffer.append(
            {self.my_globals.commands.LOOK: ""}
        )

    def fork(self) -> None:
        """
        Adds the "fork" command to the send queue
        """
        self.my_globals.response_buffer.append(
            {self.my_globals.commands.FORK: ""}
        )

    def right(self) -> None:
        """
        Adds the "right" command to the send queue
        """
        self.my_globals.response_buffer.append(
            {self.my_globals.commands.RIGHT: ""}
        )

    def empty(self) -> None:
        """
        Adds the "empty" command to the send queue
        """
        self.my_globals.response_buffer.append(
            {self.my_globals.commands.EMPTY: ""}
        )

    def eject(self) -> None:
        """
        Adds the "eject" command to the send queue
        """
        self.my_globals.response_buffer.append(
            {self.my_globals.commands.EJECT: ""}
        )

    def inventory(self) -> None:
        """
        Adds the "inventory" command to the send queue
        """
        self.my_globals.response_buffer.append(
            {self.my_globals.commands.INVENTORY: ""}
        )

    def connect_nbr(self) -> None:
        """
        Adds the "connect_nbr" command to the send queue
        """
        self.my_globals.response_buffer.append(
            {self.my_globals.commands.CONNECT_NBR: ""}
        )

    def set_obj(self) -> None:
        """
        Adds the "set_object" command to the send queue
        """
        self.my_globals.response_buffer.append(
            {self.my_globals.commands.SET_OBJECT: ""}
        )

    def take_obj(self) -> None:
        """
        Adds the "take_object" command to the send queue
        """
        self.my_globals.response_buffer.append(
            {self.my_globals.commands.TAKE_OBJECT: ""}
        )

    def incantation(self) -> None:
        """
        Adds the "incantation" command to the send queue
        """
        self.my_globals.response_buffer.append(
            {self.my_globals.commands.INCANTATION: ""}
        )

    def broadcast(self) -> None:
        """
        Adds the "broadcast" command to the send queue
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
        super().__init__(name="Logistics")
        self.sender = Sender(my_variables)
        self.constants = my_variables
        self.direction_options_list = ["forward", "left", "right"]
        self.direction_options = {
            "forward": self.sender.forward,
            "left": self.sender.left,
            "right": self.sender.right
        }
        self.text_equivalence = my_variables.translation_reference.text_equivalence
        self.random_seed = self._create_random_seed()
        self.stall = False
        self.stall_command = False

    def _create_random_seed(self) -> int:
        """_summary_
        Generate a random seed
        Returns:
            int: _description_
        """
        c_time = datetime.now()
        final_seed = c_time.hour + c_time.minute + c_time.second + c_time.microsecond
        return final_seed

    def _my_randint(self, minimum: int = 0, maximum: int = 3) -> int:
        """_summary_
            This is a function that will be used in order to provide a randome number without using the random library.
        """
        artificial_turn = 200
        counter = 0
        while counter < artificial_turn:
            pdebug(self.constants, "(logistics) In random")
            c_time = datetime.now()
            current_time = c_time.hour + c_time.minute + c_time.second + c_time.microsecond
            final_number = (current_time + self.random_seed) % (maximum + 1)
            if minimum <= final_number <= maximum:
                return final_number
            counter += 1
        return minimum

    def _can_evolve(self) -> bool:
        """_summary_
            Check if the AI can evolve.

        Returns:
            bool: _description_: True if the required ressources are present, False if the required ressources are not present
        """
        pdebug(self.constants, "(logistics) In _can_evolve:207")
        i = 0
        artificial_delay = 200
        counter = 0
        self.sender.look()
        max_i = len(self.constants.current_buffer)
        pdebug(self.constants, "(logistics) In _can_evolve:213")
        while max_i == 0 and counter < artificial_delay:
            sleep(0.1)
            pdebug(
                self.constants,
                f"(logistics) _can_evolve:Current buffer: {self._process_buffer()}"
            )
            pdebug(self.constants, "(logistics) In _can_evolve:220")
            max_i = len(self.constants.current_buffer)
            counter += 1
        if max_i == 0:
            pdebug(self.constants, "(logistics) In _can_evolve:224")
            return False
        while i < max_i:
            pdebug(self.constants, "(logistics) In _can_evolve:222")
            if Items.LINEMATE in self.constants.current_buffer[i]:
                return True
        pdebug(self.constants, "(logistics) In _can_evolve:230")
        return False

    def _change_my_mind(self) -> None:
        """_summary_
        This function is the one in charge of creating a random movement
        """
        move = self._my_randint(0, len(self.direction_options) - 1)
        self.direction_options[self.direction_options_list[move]]()
        self.stall_command = True

    def _process_buffer(self) -> list[dict[str, any]]:
        """_summary_
        Convert the buffer data to a human readable version

        Returns:
            list[dict[str, any]]: _description_: The converted buffer
        """
        converted_buffer = []
        if self.constants.current_buffer == []:
            return []
        for i in self.constants.current_buffer:
            pinfo(self.constants, f"(logistics) _process_buffer:i = {i}")
            if i == {}:
                converted_buffer.append(i)
                continue
            for j in i:
                if j in self.text_equivalence:
                    converted_buffer.append(
                        {self.text_equivalence[j]: i[j]}
                    )
                else:
                    converted_buffer.append({j: i[j]})
        return converted_buffer

    def _clear_buffer(self) -> None:
        """_summary_
        Clear the generated buffer
        """
        i = 0
        max_length = len(self.constants.current_buffer)
        while i < max_length:
            self.constants.current_buffer.pop(0)
            i += 1

    def _mainloop(self) -> int:
        """_summary_
        This is the mainloop for the program that controls the AI.

        Returns:
            int: _description_: The status of the program
        """

        self.stall = False

        while self.constants.continue_running is True:
            pdebug(self.constants, "In logistics:while")
            pdebug(
                self.constants,
                f"(logistics) current_buffer = {self._process_buffer()}"
            )
            pinfo(
                self.constants,
                f"(logistics) response_buffer = {self.constants.response_buffer}"
            )
            if Commands.DEAD in self.constants.current_buffer:
                pdebug(
                    self.constants,
                    "(logistics) The AI was ordered to commit suicide\nDying"
                )
                self.constants.continue_running = False
                self._clear_buffer()
                break
            if self.stall is True:
                pdebug(self.constants, "(logistics)  Stalling")
                continue
            if self._can_evolve() is True:
                pdebug(self.constants, "(logistics) Evolving is possible, evolving")
                self.sender.incantation()
            self._change_my_mind()
        return self.constants.success

    def run(self) -> None:
        """_summary_
        This is the function that is called when a thread is started
        """
        pinfo(self.constants, "The class Thread logistics is initialised")
        self.constants.current_status = self._mainloop()
        pwarning(
            self.constants,
            f"AI thread is exiting with {self.constants.current_status}"
        )
        pinfo(self.constants, "Exiting Logistics thread")
        sys.exit(self.constants.current_status)
