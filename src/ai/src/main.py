##
# EPITECH PROJECT, 2023
# my_zappy [fed34_prox_vm]
# File description:
# main.py
##
"""! @brief Example program for compilation reasons """

import sys

from constants import GlobalVariables as GV


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

    def __init__(self, error: int = 84, success: int = 0, ip: str = "0.0.0.0", port: int = 8080) -> None:
        self.argc = len(sys.argv)
        self.constants = GV(
            error=error,
            success=success,
            ip=ip,
            port=port
        )
        self.help_options = [
            "-h", "-help", "-?",
            "--h", "--help", "--?",
            "/h", "/help", "/?"
        ]
        self.opts = self.constants.flags
        self.constants.colourise_output.init_pallet()
        self._process_arguments()

    def __del__(self) -> None:
        """
        Function in charge of unloading the colour library when the class is destroyed.
        """
        self.constants.colourise_output.display(
            "0A",
            (),
            "Unloading ressources\n"
        )
        self.constants.colourise_output.unload_ressources()

    def _process_arguments(self) -> None:
        """
        _summary_
        This function is used to check the arguments provided by argv.
        They will be used to define some parameters that user could specify.
        """
        if (self.argc < 2 or self.argc > 7) or (self.argc == 2 and sys.argv[1] == "-help"):
            print("USAGE: ./zappy_ai -p port -n name -h machine")
            if self.argc == 2:
                sys.exit(self.constants.success)
            sys.exit(self.constants.error)

        if self.argc == 7:
            if sys.argv[1].lower() == "-p":
                self.constants.port = int(sys.argv[2])
            if sys.argv[3].lower() == "-n":
                self.constants.port = sys.argv[4]
            if sys.argv[5].lower() == "-h":
                self.constants.port = sys.argv[6]


if __name__ == "__main__":
    ERROR = 84
    SUCCESS = 0
    IP = "0.0.0.0"
    PORT = 8080
    MI = Main(
        error=ERROR,
        success=SUCCESS,
        ip=IP,
        port=PORT
    )
