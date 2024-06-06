##
# EPITECH PROJECT, 2023
# my_zappy
# File description:
# custom_functions.py
##

from constants import GlobalVariables


def perror(global_variables: GlobalVariables, string: str = "This is an error") -> None:
    """
    _summary_
    This is the function in charge of displaying an error on the error channel

    Args:
        global_variables (GlobalVariables): _description_. This is a class in charge of storing parameters that are global to the program.
        string (str, optional): _description_. Defaults to "This is an error".
    """
    global_variables.colourise_output.display(
        global_variables.message_colours.ERROR,
        (),
        ""
    )
    global_variables.beautify_error.title(f"Error: {string}")
    global_variables.colourise_output.display(
        global_variables.message_colours.DEFAULT,
        (),
        ""
    )


def pwarning(global_variables: GlobalVariables, string: str = "This is a warning") -> None:
    """
    _summary_
    This is the function in charge of displaying a warning on the standard channel

    Args:
        global_variables (GlobalVariables): _description_. This is a class in charge of storing parameters that are global to the program.
        string (str, optional): _description_. Defaults to "This is a warning".
    """
    global_variables.colourise_output.display(
        global_variables.message_colours.WARNING,
        (),
        ""
    )
    global_variables.beautify_standard.title(f"Warning: {string}")
    global_variables.colourise_output.display(
        global_variables.message_colours.DEFAULT,
        (),
        ""
    )


def psuccess(global_variables: GlobalVariables, string: str = "This is a success") -> None:
    """
    _summary_
    This is the function in charge of displaying a success on the standard channel

    Args:
        global_variables (GlobalVariables): _description_. This is a class in charge of storing parameters that are global to the program.
        string (str, optional): _description_. Defaults to "This is a warning".
    """
    global_variables.colourise_output.display(
        global_variables.message_colours.SUCCESS,
        (),
        ""
    )
    global_variables.beautify_standard.title(f"Success: {string}")
    global_variables.colourise_output.display(
        global_variables.message_colours.DEFAULT,
        (),
        ""
    )


def pinfo(global_variables: GlobalVariables, string: str = "This is a success") -> None:
    """
    _summary_
    This is the function in charge of displaying an info on the standard channel

    Args:
        global_variables (GlobalVariables): _description_. This is a class in charge of storing parameters that are global to the program.
        string (str, optional): _description_. Defaults to "This is a warning".
    """
    global_variables.colourise_output.display(
        global_variables.message_colours.INFO,
        (),
        ""
    )
    global_variables.beautify_standard.title(f"Info: {string}")
    global_variables.colourise_output.display(
        global_variables.message_colours.DEFAULT,
        (),
        ""
    )


def pdebug(global_variables: GlobalVariables, string: str = "This is a debug string") -> None:
    """
    _summary_
    This is a function in charge of displaying a string only if the debug variable is set to true (in global variables)
    """
    if global_variables.user_arguments.debug:
        global_variables.colourise_output.display(
            global_variables.message_colours.DEBUG,
            (),
            ""
        )
        global_variables.beautify_standard.title(f"Debug: {string}")
        global_variables.colourise_output.display(
            global_variables.message_colours.DEFAULT,
            (),
            ""
        )
