##
# EPITECH PROJECT, 2023
# my_zappy [fed34_prox_vm]
# File description:
# main.py
##
"""! @brief Example program for compilation reasons """

import sys


if len(sys.argv) == 2 and sys.argv[1] == "-help":
    print("USAGE: ./zappy_ai -p port -n name -h machine")
    sys.exit(0)

"""! Simple function to display the string 'Hello World!'"""
print("Hello World!")
