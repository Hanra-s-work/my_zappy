##
# EPITECH PROJECT, 2023
# my_zappy
# File description:
# receiver.py
##

import time
from socket import socket, AF_INET, SOCK_DGRAM, error as sock_error

from threading import Thread

from constants import GlobalVariables, THREAD_TIMEOUT
from custom_functions import pinfo,  psuccess, perror, pdebug, pwarning
from convert_data import ConvertData


class TCPThreader(Thread):
    """
    This is the class that will start the udp server in a new thread (that is not the main one)
    This is so that requests will not block the parent when running
    """

    def __init__(self, my_globals: GlobalVariables, error: int = 84, success: int = 0) -> None:
        """_summary_
        This is the class that will start the udp server in a new thread (that is not the main one)
        This is so that requests will not block the parent when running
        Args:
            my_globals (GlobalVariables): _description_
            error (int, optional): _description_. Defaults to 84.
            success (int, optional): _description_. Defaults to 0.
        """
        super().__init__()
        self.error = error
        self.success = success
        self.my_globals = my_globals
        self.ip = my_globals.server_data.ip
        self.port = my_globals.server_data.port
        self.server_data = my_globals.server_data
        self.server_data.welcome_message = str.encode(
            self.server_data.welcome_message
        )

    def _maintain_loop(self, udp_socket: socket) -> int:
        """_summary_
            This is the main loop of the UDP server.
            It will keep listening for incoming messages until my_globals.continue_running is set to false

        Args:
            udp_socket (_type_): _description_ : The initialised udp socket (it got created in _start_server)

        Returns:
            int: _description_ : This function will return an error if it is fatal, otherwise, it will return success
        """
        error_found = False

        pdebug(
            self.my_globals,
            f"Server is listening on: {self.ip}:{self.port}"
        )
        while self.my_globals.continue_running:
            try:
                bytes_address_pair = udp_socket.recvfrom(
                    self.server_data.buffer_size
                )
                pinfo(
                    self.my_globals,
                    f"Content of bytes_address_pair: '{bytes_address_pair}'"
                )
                if not bytes_address_pair:
                    pdebug(self.my_globals, "There is no content to be processed")
                    continue
                message, address = bytes_address_pair
                if isinstance(message, bytes):
                    message = message.decode()
                    message = message[:-1]
                psuccess(self.my_globals, f"Message from Client:{message}")
                psuccess(self.my_globals, f"Client IP Address:{address}")

                converted_data = ConvertData(message)
                cleaned_data = converted_data.to_internal()
                pdebug(self.my_globals, f"Converted data: {cleaned_data}")
                self.my_globals.current_buffer.append(cleaned_data)
                # Sending a reply to client
                # udp_socket.sendto(self.server_data.welcome_message, address)
            except sock_error as e:
                if e.errno == 11:
                    continue
                perror(self.my_globals, f"Receiver socket error: {e}")
                self.my_globals.continue_running = False
                error_found = True

        if self.my_globals.continue_running is False:
            pwarning(
                self.my_globals,
                f"The value of continue running is : {self.my_globals.continue_running}.\nThe server will now stop"
            )
        pinfo(
            self.my_globals,
            "Current buffer is:"
        )
        pinfo(
            self.my_globals,
            self.my_globals.current_buffer
        )
        if error_found is True:
            perror(self.my_globals, "Fatal error occurred. Server will now stop")
        if self.my_globals.continue_running is False:
            pdebug(self.my_globals, "The receiver loop is exiting with an error.")
            return self.error
        return self.success

    def _start_server(self) -> int:
        """_summary_
            This function will lay the base ground to make sure that the udp server will work.
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
            psuccess(self.my_globals, "UDP server socket class is initialised.")
        except sock_error as e:
            perror(
                self.my_globals,
                f"Failed to initialise udp socket class: {e}"
            )

        # Bind to address and ip
        try:
            udp_server_socket.bind((self.ip, self.port))
            psuccess(self.my_globals, "Udp socket address is bound to the port")
        except sock_error as e:
            perror(
                self.my_globals,
                f"Failed to bind udp socket to address and port: {e}"
            )

        # Make udp blocking
        try:
            pdebug(
                self.my_globals,
                f"UDP blocking is set to: {self.server_data.make_udp_wait}"
            )
            udp_server_socket.setblocking(self.server_data.make_udp_wait)
            if self.server_data.make_udp_wait:
                psuccess(
                    self.my_globals,
                    "UDP blocking is set wait for an answer"
                )
            else:
                psuccess(self.my_globals, "UDP blocking is set to non-blocking")
        except sock_error as e:
            perror(
                self.my_globals,
                f"Updating the blocking mode of the udp socket failed: {e}"
            )

        # The boot message
        pinfo(self.my_globals, self.server_data.startup_message)
        # udp_server_socket = self.my_globals.socket
        try:
            return self._maintain_loop(udp_server_socket)
        except Exception as e:
            perror(
                self.my_globals,
                f"An unexpected error occurred in the receiver loop: {e}"
            )
            return self.my_globals.error

    def run(self) -> int:
        """ 
        This function is in charge of initialising the thread as well as the program that needs to be run
        """
        return self._start_server()


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
