##
# EPITECH PROJECT, 2023
# my_zappy [fed34_prox_vm]
# File description:
# tcp_server.py
##
import sys
from socket import socket, AF_INET, SOCK_STREAM

from logistics import Logistics
from convert_data import ConvertData
from global_variables import GlobalVariables
from custom_functions import pinfo,  psuccess, perror, pdebug, pwarning


class TCPServer:
    """_summary_
    This is the class in charge of creating a tcp server and connecting to the server binary
    Args:
        Thread (_type_): _description_
    """

    def __init__(self, global_variables: GlobalVariables) -> None:
        self.global_variables = global_variables
        self.logistics: Logistics = None

    def _initialise_logistics(self) -> None:
        """_summary_
        This is the function in charge fo 
        Returns:
            int: _description_
        """
        pinfo(self.global_variables, "Initialising logistics")
        self.logistics = Logistics(self.global_variables)
        psuccess(self.global_variables, "Logistics initialised")

    def _mainloop(self, socket: socket) -> int:
        """_summary_
        The server loop that is in charge of managing the packets

        Returns:
            int: _description_
        """
        # conn, addr = socket.accept()
        conn = socket
        while self.global_variables.continue_running is True:
            data = conn.recv(self.global_variables.server_data.buffer_size)
            if not data:
                pinfo(self.global_variables, "No data received")
            pinfo(self.global_variables, f"Received data: {data.decode()}")
            if data.decode() == "exit\n":
                pinfo(self.global_variables, "Exit message received")
                self.global_variables.continue_running = False
                break
            conn.sendall("Mumble Mumble\n".encode())
        return self.global_variables.success

    def _start_tcp_socket(self) -> int:
        """_summary_
        This is the function that will lay the foundation for the tcp server.

        Returns:
            int: _description_
        """
        status = self.global_variables.success
        while self.global_variables.continue_running is True:
            s = socket(AF_INET, SOCK_STREAM)
            # s.bind(
            #     (
            #         self.global_variables.server_data.ip,
            #         self.global_variables.server_data.port
            #     )
            # )
            s.connect(
                (
                    self.global_variables.server_data.ip,
                    self.global_variables.server_data.port
                )
            )
            # s.listen()
            s.setblocking(self.global_variables.server_data.make_tcp_wait)
            s.settimeout(self.global_variables.server_data.timeout)
            pinfo(
                self.global_variables,
                self.global_variables.server_data.startup_message
            )
            tmp = self._mainloop(s)
            if tmp != self.global_variables.success:
                status = tmp
        return status

    def run(self) -> int:
        """_summary_
        This is the function in charge of starting any function that contains the code we wish to run inside the thread we started.
        """
        psuccess(self.global_variables, "TCP server thread started")
        self._initialise_logistics()
        status = self._start_tcp_socket()
        pwarning(self.global_variables, "The server is stopping")
        if status != self.global_variables.success:
            perror(
                self.global_variables,
                f"The server exited with status: {status}"
            )
            return status
        psuccess(self.global_variables, "The server exited without any errors")
        return self.global_variables.success


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
    TCPSI = TCPServer(GI)
    TCPSI.start()
    GI.colourise_output.init_pallet()
    GI.colourise_error.init_pallet()
    GI.colourise_output.unload_ressources()
    sys.exit(GI.current_status)
