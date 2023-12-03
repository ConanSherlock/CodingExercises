import re
from typing import List

INVALID_TYPE_EXCEPTION = "Invalid data type given"


class AoC2023Day3Exception(Exception):
    def __init__(self, value):
        self.value = value

    def __str__(self):
        return repr(self.value)


class Day3:
    def __init__(self):
        self._total_found_part_numbers = []
        self._number_start_indices = []
        self._number_end_indices = []
        self._symbol_start_indices = []
        self._symbol_end_indices = []
        self._found_part_numbers = []

        self._sum_part_numbers = 0

        self._number_regex_pattern = re.compile(r"(\d+)")

        self._symbol_regex_pattern = re.compile(r"[^a-zA-Z0-9]")
        self._period = "."
        self._row = 0
        self._column = 1

    def reset(self):
        self._total_found_part_numbers = []
        self._number_start_indices = []
        self._number_end_indices = []
        self._symbol_start_indices = []
        self._symbol_end_indices = []
        self._found_part_numbers = []

    def search_schematic(self, input_schematic: List[str]):
        # Checking for invalid input types
        if type(input_schematic) != list:
            raise AoC2023Day3Exception(
                "%s: %s" % (INVALID_TYPE_EXCEPTION, type(input_schematic))
            )

        for i in range(len(input_schematic)):
            sub_number_start_indices: List[int] = []
            sub_number_end_indices: List[int] = []
            sub_symbol_start_indices: List[int] = []
            sub_symbol_end_indices: List[int] = []
            sub_found_part_numbers: List[int] = []
            sub_found_part_symbols: List[str] = []

            number_search = self._number_regex_pattern.findall(input_schematic[i])

            for num in number_search:
                sub_found_part_numbers.append(int(num))
                self._number_start_indices.append(
                    list(re.finditer(num, input_schematic[i]))[
                        sub_found_part_numbers.count(int(num))
                    ].start()
                )
                self._number_end_indices.append(
                    list(re.finditer(num, input_schematic[i]))[
                        sub_found_part_numbers.count(int(num))
                    ].end()
                )

            symbol_search = self._symbol_regex_pattern.findall(input_schematic[i])
            for sym in symbol_search:
                self._symbol_start_indices.append(
                    list(re.finditer(sym, input_schematic[i]))[
                        sub_found_part_symbols.count(sym)
                    ].start()
                )
                self._symbol_end_indices.append(
                    list(re.finditer(sym, input_schematic[i]))[
                        sub_found_part_symbols.count(sym)
                    ].end()
                )

            self._number_start_indices.append(sub_number_start_indices)
            self._number_end_indices.append(sub_number_end_indices)
            self._symbol_start_indices.append(sub_symbol_start_indices)
            self._symbol_end_indices.append(sub_symbol_end_indices)
            self._found_part_numbers.append(sub_found_part_numbers)

    def get_sum_part_numbers(self) -> int:
        return self._sum_part_numbers

    def get_found_part_ids(self) -> List[int]:
        return self._total_found_part_numbers


if __name__ == "__main__":

    day3_file_path = "../../test/input_data/2023/day3_input.txt"

    day3 = Day3()

    with open(day3_file_path, "r") as input_file:
        input_schematic_data = input_file.readlines()
        day3.search_schematic(input_schematic_data)

    print("--- Day 3: Gear Ratios ---")
    print(
        "Part A Sum of all of the found part numbers value: %d"
        % day3.get_sum_part_numbers()
    )
    # print("Part B Sum of all of the cube power values: %d" % day2.get_sum_cube_power())
