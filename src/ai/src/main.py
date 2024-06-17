##
# EPITECH PROJECT, 2023
# my_zappy [fed34_prox_vm]
# File description:
# main.py
##

import sys

from tcp_server import TCPServer
from custom_functions import pinfo,  psuccess, perror, pdebug, pwarning
from global_variables import GlobalVariables, MAX_PORT_RANGE, MIN_PORT_RANGE


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
                * Free any allocated ressource that was not freed
                * Exit with the status contained in GlobalVariables
    """

    def __init__(self, error: int = 84, success: int = 0) -> None:
        self.argc: int = len(sys.argv)
        self.error: int = error
        self.success: int = success
        self.help_options: list[str] = [
            "-h", "-help", "-?",
            "--h", "--help", "--?",
            "/h", "/help", "/?"
        ]
        self.server: TCPServer = None
        self.global_variables: GlobalVariables = None

    def __del__(self) -> None:
        """
        Function in charge of unloading the colour library when the class is destroyed.
        """
        if self.global_variables is None:
            return
        if self.global_variables.colourise_output is None:
            return
        self.global_variables.colourise_output.display(
            "0A",
            (),
            "Unloading ressources\n"
        )
        self.global_variables.colourise_output.display(
            "rr",
            (),
            "End of script\n"
        )
        self.global_variables.colourise_output.unload_ressources()
        self.global_variables.colourise_error.unload_ressources()

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
                if self.argc == 8:
                    print(
                        f"The only flag allowed in the last position is: -d\nYou entered: {sys.argv[7]}"
                    )
                    return self.error
            return {"port": port, "name": name, "host": host, "debug": debug}
        return self.error

    def _check_team_name(self) -> None:
        """_summary_
        Send the current team name to the server.
        """
        user_name = self.global_variables.user_arguments.name
        if user_name == "":
            pwarning(self.global_variables, "The AI name is empty")
        pdebug(
            self.global_variables,
            f"Team name is: {self.global_variables.user_arguments.name}"
        )

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
        self.global_variables = GlobalVariables(
            error=self.error,
            success=self.success,
            ip=response["host"],
            port=response["port"],
            name=response["name"],
            debug=response["debug"]
        )
        self.global_variables.colourise_output.init_pallet()
        self.global_variables.colourise_error.init_pallet()
        self.global_variables.colourise_output.display(
            self.global_variables.message_colours.DEFAULT,
            (),
            ""
        )
        self._check_team_name()

        pinfo(self.global_variables, "Main class loaded")
        pinfo(self.global_variables, "Loading Server")
        self.server = TCPServer(self.global_variables)
        psuccess(self.global_variables, "Server is loaded")
        pinfo(self.global_variables, "Starting server")
        status = self.server.run()
        if status != self.success:
            perror(
                self.global_variables,
                f"Server stopped with status: {status}"
            )
            return status
        psuccess(self.global_variables, "Server stopped without any errors")
        return status


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
