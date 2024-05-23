##
# EPITECH PROJECT, 2023
# point_one_robot_car
# File description:
# test_constants.py
##

import unittest


class CI:
    """ Just a dummy class with data """
    ERR = 84
    ERROR = ERR
    SUCCESS = 0

# TTY colour options
    COLOURS = {
        "default": "0A",
        "prompt": "0B",
        "error": "0C",
        "success": "03",
        "info": "0D",
        "reset": "rr",
        "help_title_colour": "0E",
        "help_command_colour": "0A",
        "help_description_colour": "0F",
        "env_term_colour": "09",
        "env_shell_colour": "03",
        "env_definition_colour": "0B",
        "session_name_colour": "0D"
    }


C = CI()


class TestConstants(unittest.TestCase):
    """ Test the constants """

    def test_status_codes(self) -> None:
        """ Check the status codes """
        self.assertEqual(C.ERR, 84)
        self.assertEqual(C.ERROR, C.ERR)
        self.assertEqual(C.SUCCESS, 0)

    def test_colour_codes(self) -> None:
        """ Check the colour codes """
        expected_colours = {
            "default": "0A",
            "prompt": "0B",
            "error": "0C",
            "success": "03",
            "info": "0D",
            "reset": "rr",
            "help_title_colour": "0E",
            "help_command_colour": "0A",
            "help_description_colour": "0F",
            "env_term_colour": "09",
            "env_shell_colour": "03",
            "env_definition_colour": "0B",
            "session_name_colour": "0D"
        }
        self.assertEqual(C.COLOURS, expected_colours)


if __name__ == '__main__':
    print("Running tests for constants.py")
    unittest.main()
