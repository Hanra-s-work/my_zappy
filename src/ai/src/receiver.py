##
# EPITECH PROJECT, 2023
# my_zappy
# File description:
# receiver.py
##

from socket import socket, AF_INET, SOCK_DGRAM

from threading import Thread
from constants import GlobalVariables, THREAD_TIMEOUT
from custom_functions import pinfo,  psuccess, perror, pdebug, pwarning
from convert_data import ConvertData


class TCPThreader(Thread):
    """
    This is the class that will start the tcp server in a new thread (that is not the main one)
    This is so that requests will not block the
    """

    def __init__(self, my_globals: GlobalVariables) -> None:
        super().__init__()
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

        while self.my_globals.continue_running:
            pdebug(
                self.my_globals,
                f"Server is listening on: {self.ip}:{self.port}"
            )
            bytes_address_pair = udp_socket.recvfrom(
                self.server_data.buffer_size
            )
            message = bytes_address_pair[0]
            address = bytes_address_pair[1]
            client_msg = f"Message from Client:{message}"
            client_ip = f"Client IP Address:{address}"
            psuccess(self.my_globals, client_msg)
            psuccess(self.my_globals, client_ip)
            converted_data = ConvertData(message)
            pdebug(
                self.my_globals,
                f"Converted data: {converted_data.to_internal()}"
            )
            self.my_globals.current_buffer.append(converted_data.to_internal())
            # Sending a reply to client
            # udp_socket.sendto(self.server_data.welcome_message, address)
            if self.my_globals.continue_running is False:
                pwarning(
                    self.my_globals,
                    f"The value of continue running is : {self.my_globals.continue_running}.\nThe server will now stop"
                )

    def _start_server(self) -> int:
        """_summary_
            This function will lay the base ground to make sure that the udp server will work.
        Returns:
            int: _description_: It will return an error if it fails, otherwise, will return whatever _maintain_loop will return
        """
        # Create a datagram socket
        udp_server_socket = socket(
            family=AF_INET,
            type=SOCK_DGRAM
        )

        # Bind to address and ip
        udp_server_socket.bind((self.ip, self.port))

        # The boot message
        pinfo(self.my_globals, self.server_data.startup_message)
        try:
            return self._maintain_loop(udp_server_socket)
        except Exception as e:
            perror(self.my_globals, f"An unexpected error occurred: {e}")
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
