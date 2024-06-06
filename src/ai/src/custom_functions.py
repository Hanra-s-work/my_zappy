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
    data = f"{string}".split("\n")
    if data[-1] == "":
        data.pop()
    for i in data:
        global_variables.beautify_error.title(f"Error: {i}")
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
    data = f"{string}".split('\n')
    if data[-1] == '':
        data.pop(-1)
    for i in data:
        global_variables.beautify_standard.warning_message(i)
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
    data = f"{string}".split("\n")
    if data == '':
        data.pop(-1)
    for i in data:
        global_variables.beautify_standard.success_message(i)
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
    data = f"Info: {string}".split('\n')
    if data[-1] == '':
        data.pop(-1)
    for i in data:
        global_variables.beautify_standard.inform_message(i)
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
        global_variables.beautify_standard.message(f"Debug: {string}")
        global_variables.colourise_output.display(
            global_variables.message_colours.DEFAULT,
            (),
            ""
        )
