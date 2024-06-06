##
# EPITECH PROJECT, 2023
# my_zappy
# File description:
# receiver.py
##

import socketserver
from threading import Thread
from constants import GlobalVariables
from custom_functions import pinfo,  psuccess, perror, pdebug, pwarning


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
        self.sub_class = socketserver.BaseRequestHandler
        self.sub_class.tampered = True
        self.sub_class.my_globals = self.my_globals
        self.sub_class.handle = self.my_handle
        print(f"sub_class = {dir(self.sub_class)}")
        socketserver.BaseRequestHandler.tampered = True
        socketserver.BaseRequestHandler.my_globals = self.my_globals
        socketserver.BaseRequestHandler.handle = self.my_handle
        print(
            f"socketserver.BaseRequestHandler = {dir(socketserver.BaseRequestHandler)}")

    def my_handle(self: socketserver.BaseRequestHandler, my_self: socketserver.BaseRequestHandler = None) -> None:
        """ 
        This is a custom implementation of the function handle
        This function relies on a tampered version of the class BaseRequestHandler
        This function is not meant to be run outside of the TCPThreader class unless the required injected variables are present
        """
        if my_self is None:
            print("(my_self is none) The handle is not tampered")
        if my_self is not None and hasattr(my_self, "tampered") is True:
            print("(my_self) The handle is tampered")
        elif my_self is not None and hasattr(my_self, "tampered") is not True:
            print("(my_self) The handle is not tampered")
        else:
            print("(my_self) The handle is not tampered")
        if hasattr(self, "tampered"):
            print("(self) The class has successfully been correctly tampered with")
        else:
            print("(self) The class has not been tampered with")
        my_self.data = my_self.request.recv(1024).strip()
        print(f"Received from {my_self.client_address[0]}:")
        if hasattr(self, "tampered"):
            print("(self) The class has successfully been correctly tampered with")
            my_self.my_globals.server_data.client_address = my_self.client_address
            my_self.my_globals.raw_buffer.append(my_self.client_address[0])
        print(my_self.data)
        # # just send back the same data, but upper-cased
        # self.request.sendall(self.data.upper())

    def run(self) -> int:
        """ 
        This function is in charge of initialising the thread as well as the program that needs to be run
        """
        with socketserver.TCPServer((self.ip, self.port), self.sub_class) as server:
            print(f"Server running on : {self.ip}:{self.port}")
            # Activate the server; this will keep running until you
            # interrupt the program with Ctrl-C
            server.serve_forever()


if __name__ == "__main__":
    HOST, PORT = "localhost", 9999

    # Create the server, binding to localhost on port 9999
    GVI = GlobalVariables(0, 84, "0.0.0.0", 8080)
    TTI = TCPThreader(
        my_globals=GVI
    )
    TTI.start()
    # TTI.join()
