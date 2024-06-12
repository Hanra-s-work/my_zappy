##
# EPITECH PROJECT, 2023
# my_zappy [fed34_prox_vm]
# File description:
# main.py
##
"""! @brief Example program for compilation reasons """

import sys

from constants import GlobalVariables, MAX_PORT_RANGE, MIN_PORT_RANGE, THREAD_TIMEOUT
from custom_functions import pinfo,  psuccess, perror, pdebug, pwarning
from sender import SenderThread
from receiver import TCPThreader
from convert_data import ConvertData
from logistics import LogicsticsThread


class Main:
    """ 
        This is the main class of the program.
        This class is responsible for calling the three main steps of the program.
        These steps are:
        * Initialisation:
                * Check arguments
                * Create listener on a new thread
                * Create sender on a new thread
        * Launch mainloop (skipped if error occurs before this step)
        * When the program ends:
                * If the reason was an error:
                        * Display the error
                * Kill all created threads
                * Free any allocated ressource that was not freed
                * Exit with the status contained in GlobalVariables
    """

    def __init__(self, error: int = 84, success: int = 0) -> None:
        self.argc = len(sys.argv)
        self.success = success
        self.error = error
        self.help_options = [
            "-h", "-help", "-?",
            "--h", "--help", "--?",
            "/h", "/help", "/?"
        ]
        self.sender = None
        self.server = None
        self.logistics = None
        self.constants = None

    def __del__(self) -> None:
        """
        Function in charge of unloading the colour library when the class is destroyed.
        """
        self._stop_threads()
        if self.constants is None:
            return
        if self.constants.colourise_output is None:
            return
        self.constants.colourise_output.display(
            "0A",
            (),
            "Unloading ressources\n"
        )
        self.constants.colourise_output.display("rr", (), "End of script\n")
        self.constants.colourise_output.unload_ressources()
        self.constants.colourise_error.unload_ressources()

    def _process_arguments(self) -> int:
        """
        _summary_
        This function is used to check the arguments provided by argv.
        They will be used to define some parameters that user could specify.
        This function is also the one in charge of displaying the help section when required.
        """
        if (self.argc not in (7, 8)):
            print("USAGE: ./zappy_ai -p port -n name -h machine")
            if self.argc == 2 and sys.argv[1] in self.help_options:
                return self.success
            return self.error

        if self.argc == 7 or self.argc == 8:
            if sys.argv[1].lower() == "-p":
                if sys.argv[2].isnumeric() is False:
                    print(
                        f"Error: The -p flag must be a positive whole number that ranges between {MIN_PORT_RANGE} and {MAX_PORT_RANGE}\nPlease run {sys.argv[0]} --help"
                    )
                    return self.error
                port = int(sys.argv[2])
                if port < MIN_PORT_RANGE or port > MAX_PORT_RANGE:
                    print(
                        f"Error: The -p flag must be a positive whole number that ranges between {MIN_PORT_RANGE} and {MAX_PORT_RANGE}\nPlease run {sys.argv[0]} --help"
                    )
                    return self.error
            else:
                print(
                    f"Error: The -p flag is missing\nPlease run {sys.argv[0]} --help"
                )
                return self.error
            if sys.argv[3].lower() == "-n":
                name = sys.argv[4]
            else:
                print(
                    f"Error: The -n flag is missing\nPlease run {sys.argv[0]} --help"
                )
                return self.error
            if sys.argv[5].lower() == "-h":
                host = sys.argv[6]
            else:
                print(
                    f"Error: The -h flag is missing\nPlease run {sys.argv[0]} --help"
                )
                return self.error
            if self.argc == 8 and sys.argv[7].lower() == "-d":
                debug = True
            else:
                debug = False
            return {"port": port, "name": name, "host": host, "debug": debug}
        return self.error

    def _start_threads(self) -> None:
        """
        _summary_
        This function is in charge of starting the 3 threads that are used in this program:
        * The thread for the process that will receive the requests
        * The thread for the process that will send the requests
        * The thread for the process that will be running the brain
        """
        pdebug(self.constants, "Starting threads")
        pdebug(self.constants, "Starting sender")
        self.sender.start()
        self.constants.created_threads["sender"] = self.sender
        pdebug(self.constants, "Sender thread started")
        pdebug(self.constants, "Starting receiver")
        self.server.start()
        self.constants.created_threads["receiver"] = self.server
        pdebug(self.constants, "Receiver thread started")
        pdebug(self.constants, "Starting logistics")
        self.logistics.start()
        self.constants.created_threads["logistics"] = self.logistics
        pdebug(self.constants, "Logistics thread started")

    def _stop_threads(self) -> None:
        """_summary_
        This function is called when we wish to terminate the program.
        This function will attempt to terminate the threads that have been started in the main function.
        """
        if self.constants is None or self.constants.colourise_output is None:
            data = [self.sender, self.server, self.logistics]
            for i in data:
                if i is None:
                    continue
                i.join(THREAD_TIMEOUT)
            return
        if len(self.constants.created_threads) == 0:
            return
        for key, value in self.constants.created_threads.items():
            pdebug(self.constants, f"Checking {key}")
            if value is None:
                pdebug(
                    self.constants,
                    f"{key} is empty, there is thus nothing to stop"
                )
                continue
            pdebug(self.constants, f"{key} is not empty, stopping")
            data = value.join(THREAD_TIMEOUT)
            self.constants.created_threads[key] = None
            pdebug(self.constants, f"{key} has stopped and returned: {data}")
        return

    def _stay_alive(self) -> int:
        """
        _sumary_
        This function's role is to check on the threads and know when it is time to stop the program
        """
        while self.constants.continue_running:
            self.constants.current_status = self.success
            tt = input("pause press enter to continue...\n")
            self.constants.continue_running = False
            self.constants.current_buffer.append(
                ConvertData("dead").to_internal()
            )
        self._stop_threads()
        return self.constants.current_status

    def _bufferise_team_name(self) -> None:
        """_summary_
        Send the current team name to the server.
        """
        user_name = self.constants.user_arguments.name
        if user_name == "":
            pwarning(self.constants, "The AI name is empty")
        self.constants.response_buffer.append(user_name)

    def main(self) -> int:
        """
        _sumary_
        The main function of the program.
        This function is the one in charge of:
        * Parsing the arguments
        * Creating the threads
        * Starting the threads
        """
        response = self._process_arguments()
        if isinstance(response, int):
            if response != self.success:
                print(
                    f"One or more errors have occurred\nPlease run {sys.argv[0]} --help for more information"
                )
            return response
        self.constants = GlobalVariables(
            error=self.error,
            success=self.success,
            ip=response["host"],
            port=response["port"],
            name=response["name"],
            debug=response["debug"]
        )
        self.constants.colourise_output.init_pallet()
        self.constants.colourise_error.init_pallet()
        self.constants.colourise_output.display(
            self.constants.message_colours.DEFAULT,
            (),
            ""
        )
        pdebug(
            self.constants,
            f"Thread timeout is set to: {THREAD_TIMEOUT} seconds"
        )
        self._bufferise_team_name()

        pinfo(self.constants, "Main class loaded")
        pinfo(self.constants, "Loading Sender")
        self.sender = SenderThread(self.constants)
        pdebug(self.constants, "Thread Sender is loaded")
        pinfo(self.constants, "Loading Receiver")
        self.server = TCPThreader(self.constants)
        pdebug(self.constants, "Receiver is loaded")
        pinfo(self.constants, "Loading Logistics")
        self.logistics = LogicsticsThread(self.constants)
        pdebug(self.constants, "Thread Logistics is loaded")
        pinfo(self.constants, "Thread classes loaded")
        perror(self.constants, "This is a sample error message")
        self._start_threads()
        psuccess(self.constants, "Threads launched")
        return self._stay_alive()


if __name__ == "__main__":
    ERROR = 84
    SUCCESS = 0
    IP = "0.0.0.0"
    PORT = 8080
    MI = Main(
        error=ERROR,
        success=SUCCESS
    )
    sys.exit(MI.main())
