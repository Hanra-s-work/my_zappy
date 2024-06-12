##
# EPITECH PROJECT, 2023
# my_zappy
# File description:
# inventory_args.py
##

class Items:
    """
    _summary_
    This is a python version of an enum.
    This enum hosts a set of variables referencing the available types of objects that can be gathered from the field
    """
    FOOD: int = 1
    LINEMATE: int = 2
    DERAUMERE: int = 3
    SIBUR: int = 4
    MENDIANE: int = 5
    PHIRAS: int = 6
    THYSTAME: int = 7


class Tester:
    """_summary_
    This is a class in charge of simulating the environement.
    """

    def __init__(self) -> None:

        self.item_string_to_class = {
            "food": Items.FOOD,
            "linemate": Items.LINEMATE,
            "deraumere": Items.DERAUMERE,
            "sibur": Items.SIBUR,
            "mendiane": Items.MENDIANE,
            "phiras": Items.PHIRAS,
            "thystame": Items.THYSTAME
        }

        self.item_class_to_string = {
            Items.FOOD: "food",
            Items.LINEMATE: "linemate",
            Items.DERAUMERE: "deraumere",
            Items.SIBUR: "sibur",
            Items.MENDIANE: "mendiane",
            Items.PHIRAS: "phiras",
            Items.THYSTAME: "thystame"
        }

    def convert_data(self, args: str) -> list[dict[str, int]]:
        """_summary_
        Convert a string to the internal researched format.

        Args:
            args (str): _description_

        Returns:
            list[dict[str, int]]: _description_
        """
        result = []
        data = args.split(', ')
        if "[" in data[0]:
            data[0] = data[0][1:]
        if "]" in data[-1]:
            data[-1] = data[-1][:-1]
        for i in data:
            print(f"i = {i}")
            if " " in i:
                term, definition = i.split(" ", 1)
                term = term.lower()
                if definition.isnumeric():
                    definition = int(definition)
                else:
                    continue
                if term in self.item_string_to_class:
                    term = self.item_string_to_class[term]
                else:
                    continue
                result.append({term: definition})
            else:
                term = i.lower()
                if term in self.item_string_to_class:
                    term = self.item_string_to_class[term]
                else:
                    continue
                result.append({term: definition})

        return result


Input = "[linemate n, NOT_AN_ITEM 20, NOT_A_FOOD, food, sibur 1, ...]"

TI = Tester()

output = TI.convert_data(Input)

print(f"Converted output: {output}")
