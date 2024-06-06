##
# EPITECH PROJECT, 2023
# my_zappy
# File description:
# class_overides.py
##

"""
    _summary_
    This file is in charge of hosting classes that will override the python standard classes in order to add functionality that could be considered as missing
"""


class MyStr(str):
    """
    _summary_
    This is a revisit of the str class in which some functions that were considered missing will be implemented
    """

    def isfloat(self) -> bool:
        """
        _summary_
        This is a function that will see if the input is of type float or not
        return:
            * if float:
                    * true
            * else:
                    * false
        """
        string = self.__str__()
        comma_found = False
        for i in string:
            if i == '.' and comma_found:
                return False
            if i == '.':
                comma_found = True
            if i.isnumeric() is False:
                return False
        return True
