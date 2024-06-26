##
# EPITECH PROJECT, 2023
# my_zappy
# File description:
# sender.py
##

import sys
from socket import socket, AF_INET, SOCK_STREAM, error as sock_error, timeout as sock_timeout
from threading import Thread

from constants import GlobalVariables, Commands
from convert_data import ConvertData
from custom_functions import pinfo,  psuccess, perror, pdebug, pwarning


class SenderThread(Thread):
    """_summary_
    This is the class that will start the tcp server in a new thread (that is not the main one)
    This is so that requests will not block the parent when running

    Args:
        Thread (_type_): _description_
    """

    def __init__(self, my_globals: GlobalVariables, error: int = 84, success: int = 0) -> None:
        """_summary_
        This is the class that will start the tcp server in a new thread (that is not the main one)
        This is so that requests will not block the parent when running

        Args:
            my_variables (GlobalVariables): _description_
        """
        super().__init__(name="Sender")
        self.error = error
        self.success = success
        self.my_globals = my_globals
        self.sender_data = my_globals.sender_data
        self.ip = my_globals.sender_data.ip
        self.port = my_globals.sender_data.port
        self.sent_data: list = []

    def _send_tcp_message(self, tcp_socket: socket, message: dict[Commands, any]) -> int:
        """_summary_
        This function aims to send a tcp message and return the send status

        Args:
            tcp_socket (socket): _description_: The tcp active connection
            message (dict[Commands, any]): _description_: The message to send

        Returns:
            int: _description_: The response status of the send command
        """
        converted_data = ConvertData(message)
        cleaned_data = converted_data.to_external()
        pdebug(self.my_globals, f"(sender) Converted data: {cleaned_data}")
        data_bytes = cleaned_data.encode()
        pdebug(self.my_globals, f"(sender) Encoded data: {data_bytes}")
        self.sent_data[-1]["sent_data"] = data_bytes
        send_status = tcp_socket.send(data_bytes)
        return send_status

    def _get_tcp_response(self, tcp_socket: socket) -> int:
        """_summary_
        This function aims to gather the response sent by the peer to which we spoke.

        Args:
            tcp_socket (socket): _description_:  The tcp active connection

        Returns:
            int: _description_: The response status of the command for receiving responses
        """
        tcp_response = tcp_socket.recv(self.sender_data.buffer_size)
        converted_data = ConvertData(
            tcp_response,
            error=self.error,
            success=self.success
        )
        if converted_data != self.success:
            perror(
                self.my_globals,
                f"(sender) Received data that could not be processed: {tcp_response}"
            )
            return converted_data
        converted_response = converted_data.to_internal()
        self.my_globals.current_buffer.append(converted_response)
        self.sent_data[-1]["received_data"] = converted_response
        return self.success

    def _maintain_loop(self, tcp_socket: socket) -> int:
        """_summary_

        Args:
            tcp_socket (socket): _description_: This is the tcp socket used in order to communicate with the network

        Returns:
            int: _description_: This function will return an error if it is fatal, otherwise, it will return success
        """
        error_found = False
        index = 0

        pdebug(
            self.my_globals,
            f"(sender) Sender is listening on: {self.ip}:{self.port}"
        )
        conn, addr = tcp_socket.accept()
        pinfo(self.my_globals, f"(sender) Client {addr} is connected")
        while self.my_globals.continue_running:
            if self.my_globals.response_buffer == []:
                continue
            # conn, addr = tcp_socket.accept()
            # pinfo(self.my_globals, f"Client {addr} is connected")
            try:
                index += 1
                self.sent_data.append({"id": index})
                message = self.my_globals.response_buffer.pop(0)
                send_status = self._send_tcp_message(conn, message)
                if send_status != 0:
                    perror(
                        self.my_globals,
                        f"(sender) Send error code: {send_status}"
                    )
                    continue
                psuccess(
                    self.my_globals,
                    "(sender) Message sent successfully !"
                )
                response_status = self._get_tcp_response(conn)
                if response_status != self.success:
                    continue
                psuccess(
                    self.my_globals,
                    "(sender) Response received successfully !"
                )

            except sock_timeout as e:
                pwarning(
                    self.my_globals,
                    f"(sender) Socket operation timed out: {e}"
                )

            except sock_error as e:
                if e.errno == 11:
                    continue
                perror(self.my_globals, f"(sender) Receiver socket error: {e}")
                self.my_globals.continue_running = False
                error_found = True

        if self.my_globals.continue_running is False:
            pwarning(
                self.my_globals,
                f"The value of continue running is : {self.my_globals.continue_running}.\nThe server will now stop"
            )
        pinfo(
            self.my_globals,
            "(sender) Current buffer is:"
        )
        pinfo(
            self.my_globals,
            self.sent_data
        )
        if error_found is True:
            perror(
                self.my_globals,
                "(sender) Fatal error occurred. Server will now stop"
            )
        if self.my_globals.continue_running is False and error_found is True:
            pdebug(
                self.my_globals,
                "(sender) The receiver loop is exiting with an error."
            )
            return self.error
        return self.success

    def _start_server(self) -> int:
        """_summary_
            This function will lay the ground to make sure that the tcp server will work.
        Returns:
            int: _description_: It will return an error if it fails, otherwise, will return whatever _maintain_loop will return
        """
        try:
            socket_tcp = socket(
                family=AF_INET,
                type=SOCK_STREAM
            )
            psuccess(self.my_globals, "(sender) Tcp socket class initialised")
        except sock_error as e:
            perror(self.my_globals, f"(sender) Failed to create socket: {e}")

        try:
            socket_tcp.bind((self.ip, self.port))
            psuccess(
                self.my_globals,
                "(sender) Socket connected to sender server"
            )
        except sock_error as e:
            perror(
                self.my_globals,
                f"(sender) Failed to connect to sender server: {e}"
            )

        try:
            socket_tcp.setblocking(self.sender_data.make_tcp_wait)
            socket_tcp.settimeout(self.sender_data.timeout)
            if self.sender_data.make_tcp_wait:
                psuccess(
                    self.my_globals,
                    "(sender) Socket set to blocking mode"
                )
            else:
                psuccess(
                    self.my_globals,
                    "(sender) Socket set to non-blocking mode"
                )
            psuccess(
                self.my_globals,
                f"(sender) Timeout is set to {self.sender_data.timeout}"
            )
        except sock_error as e:
            perror(
                self.my_globals,
                f"(sender) Failed to set socket options: {e}"
            )

        # socket_tcp = self.my_globals.socket
        self.my_globals.sender_ready = True
        try:
            return self._maintain_loop(socket_tcp)
        except Exception as e:
            perror(
                self.my_globals,
                f"(sender) An unexpected error occurred in the sender loop: {e}"
            )
            return self.my_globals.error

    def run(self) -> int:
        """_summary_
        This is the function that is called when a thread is started
        """
        # time.sleep(5)
        pinfo(self.my_globals, "(sender) The class Thread sender is initialised")
        status = self._start_server()
        pwarning(
            self.my_globals,
            f"(sender) The class Thread sender has stopped with status: {status}!"
        )
        self.my_globals.current_status = status
        pinfo(self.my_globals, "Exiting Sender thread")
        sys.exit(status)
