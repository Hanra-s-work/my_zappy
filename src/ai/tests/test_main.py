##
# EPITECH PROJECT, 2023
# point_one_robot_car
# File description:
# test_main.py
##

import sys
import unittest
from unittest import mock


def test_function() -> None:
    """ A test function """
    print("Test function")


def test_function2() -> str:
    """ A test function """
    return "Test function2"


def test_function3() -> str:
    """ A test function """
    return input("Test function3:")


def test_function4() -> None:
    """ A test function """
    print(f"You have entered: {input('Test function4:')}")


class TestMainFunctions(unittest.TestCase):
    """ Test the main functions """

    def setUp(self):
        """ Setup method that is called before each test """
        self.debug = False

    def print_debug(self, string: str, *args, **kwargs) -> None:
        """ Print a debug message """
        if self.debug:
            print(f"DEBUG: {string}", file=sys.stderr, *args, **kwargs)

    def test_test1(self) -> None:
        """ Test the test1 function """
        self.print_debug("test_test1")
        self.assertIsNone(test_function())

    def test_test2(self) -> None:
        """ Test the test2 function """
        self.print_debug("test_test2")
        self.assertEqual(test_function2(), "Test function2")

    def test_test3(self) -> None:
        """ Test the test3 function """
        self.print_debug("test_test3")
        usr_input = "dadada"
        with mock.patch("builtins.input", return_value=usr_input):
            self.assertEqual(test_function3(), usr_input)

    def test_test4(self) -> None:
        """ Test the test4 function """
        self.print_debug("test_test4")
        usr_input = "dadada"
        with mock.patch("builtins.input", return_value=usr_input):
            with mock.patch("builtins.print", return_value=None) as mock_print:
                test_function4()
                mock_print.assert_called_once_with(
                    f"You have entered: {usr_input}")

    def test_test1_mock(self) -> None:
        """ Test the test1 function with a mock """
        self.print_debug("test_test1_mock")
        with mock.patch("builtins.print", return_value=None) as mock_print:
            test_function()
            mock_print.assert_called_once_with("Test function")

    def test_test2_mock(self) -> None:
        """ Test the test2 function with a mock """
        self.print_debug("test_test2_mock")
        with mock.patch("builtins.print", return_value=None) as mock_print:
            test_function2()
            mock_print.assert_not_called()

    def test_test3_mock(self) -> None:
        """ Test the test3 function with a mock """
        self.print_debug("test_test3_mock")
        usr_input_mock = "dadada"
        with mock.patch("builtins.input", side_effect=[usr_input_mock]) as mock_input:
            self.assertEqual(test_function3(), usr_input_mock)
            mock_input.assert_called_once_with("Test function3:")

    def test_test4_mock(self) -> None:
        """ Test the test4 function with a mock """
        self.print_debug("test_test4_mock")
        usr_input_mock = "dadada"
        with mock.patch("builtins.print", return_value=None) as mock_print:
            with mock.patch("builtins.input", side_effect=[usr_input_mock]) as mock_input:
                test_function4()
                mock_input.assert_called_once_with("Test function4:")
                mock_print.assert_called_once_with(
                    f"You have entered: {usr_input_mock}")


if __name__ == "__main__":
    print("Running tests for main.py...")
    unittest.main()
