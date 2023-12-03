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
        self._number_start_indices = []
        self._number_end_indices = []
        self._symbol_start_indices = []
        self._symbol_end_indices = []
        self._found_part_numbers = []
        self._found_numbers_list = []
        self._sum_part_numbers = 0

        self._number_regex_pattern = re.compile(r"(\d+)")

        self._symbol_regex_pattern = re.compile(r"[^a-zA-Z0-9]")
        self._period = "."
        self._row = 0
        self._column = 1

    def reset(self):
        self._number_start_indices = []
        self._number_end_indices = []
        self._symbol_start_indices = []
        self._symbol_end_indices = []
        self._found_part_numbers = []
        self._found_numbers_list = []
        self._sum_part_numbers = 0

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
                sub_number_start_indices.append(
                    list(re.finditer(num, input_schematic[i]))[
                        sub_found_part_numbers.count(int(num)) - 1
                    ].start()
                )
                sub_number_end_indices.append(
                    list(re.finditer(num, input_schematic[i]))[
                        sub_found_part_numbers.count(int(num)) - 1
                    ].end()
                )

            symbol_search = self._symbol_regex_pattern.findall(input_schematic[i])
            for sym in symbol_search:
                if sym == self._period or sym == "\n":
                    continue
                sub_symbol_start_indices.append(
                    list(re.finditer(re.escape(sym), input_schematic[i]))[
                        sub_found_part_symbols.count(sym) - 1
                    ].start()
                )
                sub_symbol_end_indices.append(
                    list(re.finditer(re.escape(sym), input_schematic[i]))[
                        sub_found_part_symbols.count(sym) - 1
                    ].end()
                )

            self._number_start_indices.append(sub_number_start_indices)
            self._number_end_indices.append(sub_number_end_indices)
            self._symbol_start_indices.append(sub_symbol_start_indices)
            self._symbol_end_indices.append(sub_symbol_end_indices)
            self._found_numbers_list.append(sub_found_part_numbers)

        for sub_numbers, sub_number_start_index, sub_number_end_index, row in zip(
            self._found_numbers_list,
            self._number_start_indices,
            self._number_end_indices,
            range(len(self._found_numbers_list)),
        ):
            self._find_part_numbers(
                sub_numbers, sub_number_start_index, sub_number_end_index, row
            )
        self._sum_part_numbers = sum(self._found_part_numbers)

    def _find_part_numbers(
        self,
        sub_numbers: List[int],
        sub_number_start_index: List[int],
        sub_number_end_index: List[int],
        row: int,
    ):
        valid_part_number_found = False
        for number, number_start_index, number_end_index in zip(
            sub_numbers, sub_number_start_index, sub_number_end_index
        ):
            if row == 0:
                search_range = [0, 1]
            elif row + 1 == len(self._symbol_start_indices):
                search_range = list(range(row - 1, row + 1))
            else:
                search_range = list(range(row - 1, row + 2))

            for i in search_range:
                for symbol_start_index, symbol_end_index in zip(
                    self._symbol_start_indices[i], self._symbol_end_indices[i]
                ):
                    if (
                        symbol_start_index - 1
                        <= number_start_index
                        <= symbol_start_index + 1
                    ):
                        self._found_part_numbers.append(number)
                        valid_part_number_found = True
                        break
                    if (
                        symbol_start_index - 1
                        <= number_end_index - 1
                        <= symbol_start_index + 1
                    ):
                        self._found_part_numbers.append(number)
                        valid_part_number_found = True
                        break
                if valid_part_number_found:
                    valid_part_number_found = False
                    break

    def get_sum_part_numbers(self) -> int:
        return self._sum_part_numbers

    def get_found_part_ids(self) -> List[int]:
        return self._found_part_numbers


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
