##
# EPITECH PROJECT, 2023
# my_zappy
# File description:
# receiver.py
##

import sys
import time
from socket import socket, AF_INET, SOCK_DGRAM, error as sock_error

from threading import Thread

from constants import GlobalVariables, THREAD_TIMEOUT, Commands
from custom_functions import pinfo,  psuccess, perror, pdebug, pwarning
from convert_data import ConvertData


class TCPThreader(Thread):
    """
    This is the class that will start the UDP server in a new thread (that is not the main one)
    This is so that requests will not block the parent when running
    """

    def __init__(self, my_globals: GlobalVariables, error: int = 84, success: int = 0) -> None:
        """_summary_
        This is the class that will start the UDP server in a new thread (that is not the main one)
        This is so that requests will not block the parent when running
        Args:
            my_globals (GlobalVariables): _description_
            error (int, optional): _description_. Defaults to 84.
            success (int, optional): _description_. Defaults to 0.
        """
        super().__init__(name="Receiver")
        self.error = error
        self.success = success
        self.my_globals = my_globals
        self.ip = my_globals.server_data.ip
        self.port = my_globals.server_data.port
        self.server_data = my_globals.server_data
        self.server_data.welcome_message = str.encode(
            self.server_data.welcome_message
        )

    def _humanatate_nodes(self, nodes: dict[Commands, any]) -> str:
        """_summary_
        Convert the buffer data to a human readable version

        Returns:
            list[dict[str, any]]: _description_: The converted buffer
        """
        converted_node = ""
        pinfo(self.my_globals, f"Humanating = {nodes}")
        if isinstance(nodes, dict) is False:
            pdebug(
                self.my_globals,
                "(receiver) _humanate_nodes:nodes are not of type dict"
            )
            return f"{nodes}"
        if nodes == {}:
            pdebug(
                self.my_globals,
                "(receiver) _humanate_nodes:nodes is equal to {}"
            )
            return str(nodes)
        converted_node += "{"
        pdebug(self.my_globals, "(receiver) _humanate_nodes:Going to loop")
        for j in nodes:
            if j in self.my_globals.translation_reference.text_equivalence:
                pdebug(
                    self.my_globals,
                    "(receiver) _humanate_nodes:j is found in self.my_globals.translation_reference.text_equivalence"
                )
                pdebug(self.my_globals, f"nodes[{j}] = {nodes[j]}")
                converted_node += f"{self.my_globals.translation_reference.text_equivalence[j]}: {nodes[j]}"
            else:
                pdebug(
                    self.my_globals,
                    "(receiver) _humanate_nodes:j is not found in self.my_globals.translation_reference.text_equivalence"
                )
                converted_node += f"{j}: {nodes[j]}"
            converted_node += ','
        pdebug(self.my_globals, "(receiver) _humanate_nodes:Out of the for loop")
        converted_node = converted_node[:-1]
        converted_node += "}"
        pdebug(self.my_globals, "(receiver) _humanate_nodes:Out of Humanating")
        return converted_node

    def _send_buffer_list(self, udp_socket: socket, address) -> None:
        """_summary_
        This function is in charge of sending the content of the buffer

        Args:
            udp_socket (socket): _description_: This is the active connection used to send data
        """
        for i in self.my_globals.response_buffer:
            try:
                pinfo(self.my_globals, f"(receiver) Raw data: '{i}'")
                pinfo(
                    self.my_globals,
                    f"(receiver) Humanated data: {self._humanatate_nodes(i)}"
                )
                converted = ConvertData(
                    i,
                    self.error,
                    self.success
                )
                pinfo(
                    self.my_globals,
                    f"(receiver) Converted data class: '{converted}'"
                )
                data = converted.to_external()
                pinfo(
                    self.my_globals,
                    f"(receiver) Converted data: '{data}'"
                )
                udp_socket.sendto(str.encode(data), address)
                self.my_globals.response_buffer.pop(0)
            except Exception as e:
                perror(
                    self.my_globals,
                    f"(receiver) Failed to send data: '{e}'"
                )

    def _maintain_loop(self, udp_socket: socket) -> int:
        """_summary_
            This is the main loop of the UDP server.
            It will keep listening for incoming messages until my_globals.continue_running is set to false

        Args:
            udp_socket (_type_): _description_ : The initialised UDP socket (it got created in _start_server)

        Returns:
            int: _description_ : This function will return an error if it is fatal, otherwise, it will return success
        """
        error_found = False

        pdebug(
            self.my_globals,
            f"(receiver) Server is listening on: '{self.ip}:{self.port}'"
        )
        while self.my_globals.continue_running is True:
            # pdebug(self.my_globals, "In receiver:while")
            try:
                bytes_address_pair = udp_socket.recvfrom(
                    self.server_data.buffer_size
                )
                pinfo(
                    self.my_globals,
                    f"(receiver) Content of bytes_address_pair: '{bytes_address_pair}'"
                )
                if not bytes_address_pair:
                    pdebug(
                        self.my_globals,
                        "(receiver) There is no content to be processed"
                    )
                    continue
                message, address = bytes_address_pair
                if isinstance(message, bytes):
                    message = message.decode()
                    message = message[:-1]
                psuccess(
                    self.my_globals,
                    f"(receiver) Message from Client: '{message}'"
                )
                psuccess(
                    self.my_globals,
                    f"(receiver) Client IP Address: '{address}'"
                )

                converted_data = ConvertData(message)
                cleaned_data = converted_data.to_internal()
                pdebug(
                    self.my_globals,
                    f"(receiver) Converted data: '{cleaned_data}'"
                )
                self.my_globals.current_buffer.append(cleaned_data)
                self._send_buffer_list(udp_socket, address)
                # Sending a reply to client
                # udp_socket.sendto(self.server_data.welcome_message, address)
                # udp_socket.sendto("DATA RECEIVED".encode(), address)

            except sock_error as e:
                if e.errno == 11:
                    continue
                perror(
                    self.my_globals,
                    f"(receiver) Receiver socket error: '{e}'"
                )
                self.my_globals.continue_running = False
                error_found = True

        if self.my_globals.continue_running is False:
            pwarning(
                self.my_globals,
                f"(receiver) The value of continue running is : '{self.my_globals.continue_running}'.\nThe server will now stop"
            )
        pinfo(
            self.my_globals,
            "(receiver) Current buffer is:"
        )
        pinfo(
            self.my_globals,
            self.my_globals.current_buffer
        )
        if error_found is True:
            perror(
                self.my_globals,
                "(receiver) Fatal error occurred. Server will now stop"
            )
        if self.my_globals.continue_running is False and error_found is True:
            pdebug(
                self.my_globals,
                "(receiver) The receiver loop is exiting with an error."
            )
            return self.error
        return self.success

    def _start_server(self) -> int:
        """_summary_
            This function will lay the base ground to make sure that the UDP server will work.
        Returns:
            int: _description_: It will return an error if it fails, otherwise, will return whatever _maintain_loop will return
        """
        # Stall while tcp server is starting
        while self.my_globals.sender_ready is False and self.my_globals.continue_running:
            time.sleep(0.5)

        # Create a datagram socket
        try:
            udp_server_socket = socket(
                family=AF_INET,
                type=SOCK_DGRAM
            )
            psuccess(
                self.my_globals,
                "(receiver) UDP server socket class is initialised."
            )
        except sock_error as e:
            perror(
                self.my_globals,
                f"(receiver) Failed to initialise UDP socket class: '{e}'"
            )

        # Bind to address and ip
        try:
            udp_server_socket.bind((self.ip, self.port))
            psuccess(
                self.my_globals,
                "(receiver) UDP socket address is bound to the port"
            )
        except sock_error as e:
            perror(
                self.my_globals,
                f"(receiver) Failed to bind UDP socket to address and port: '{e}'"
            )

        # Make UDP blocking
        try:
            pdebug(
                self.my_globals,
                f"(receiver) UDP blocking is set to: {self.server_data.make_udp_wait}"
            )
            udp_server_socket.setblocking(self.server_data.make_udp_wait)
            if self.server_data.make_udp_wait:
                psuccess(
                    self.my_globals,
                    "(receiver) UDP blocking is set wait for an answer"
                )
            else:
                psuccess(
                    self.my_globals,
                    "(receiver) UDP blocking is set to non-blocking"
                )
        except sock_error as e:
            perror(
                self.my_globals,
                f"(receiver) Updating the blocking mode of the UDP socket failed: '{e}'"
            )

        # The boot message
        pinfo(self.my_globals, self.server_data.startup_message)
        # udp_server_socket = self.my_globals.socket
        try:
            return self._maintain_loop(udp_server_socket)
        except Exception as e:
            perror(
                self.my_globals,
                f"(receiver) An unexpected error occurred in the receiver loop: '{e}'"
            )
            return self.my_globals.error

    def run(self) -> int:
        """ 
        This function is in charge of initialising the thread as well as the program that needs to be run
        """
        pinfo(self.my_globals, "(receiver) The class Thread receiver is initialised")
        status = self._start_server()
        pwarning(
            self.my_globals,
            f"(receiver) The class Thread receiver has stopped with status: '{status}'!"
        )
        self.my_globals.current_status = status
        pdebug(self.my_globals, "Exiting receiver thread.")
        sys.exit(status)


if __name__ == "__main__":
    HOST, PORT = "localhost", 9000
    ERROR, SUCCESS = 84, 0

    # Create the server, binding to localhost on port 9000
    GVI = GlobalVariables(SUCCESS, ERROR, HOST, PORT, debug=True)
    GVI.colourise_output.init_pallet()
    TTI = TCPThreader(
        my_globals=GVI
    )
    TTI.start()
    input("Pause, press enter to continue...")
    TTI.my_globals.continue_running = False
    TTI.join(THREAD_TIMEOUT)
    GVI.colourise_output.unload_ressources()
