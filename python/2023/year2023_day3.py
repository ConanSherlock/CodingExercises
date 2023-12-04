import re
import os
from typing import List


class AoC2023Day3Exception(Exception):
    def __init__(self, value):
        self.value = value

    def __str__(self):
        return repr(self.value)


INVALID_TYPE_EXCEPTION = "Invalid data type given"
NUMBER_REGEX_PATTERN = re.compile(r"(\d+)")
SYMBOL_REGEX_PATTERN = re.compile(r"[^a-zA-Z0-9]")


class Day3:
    def __init__(self):
        self._number_start_indices = []
        self._number_end_indices = []
        self._symbol_start_indices = []
        self._found_part_numbers = []
        self._found_numbers_list = []
        self._sum_part_numbers = 0

        self._period = "."
        self._newline = "\n"

    def reset(self):
        self._number_start_indices = []
        self._number_end_indices = []
        self._symbol_start_indices = []
        self._found_part_numbers = []
        self._found_numbers_list = []
        self._sum_part_numbers = 0

    def search_schematic(self, input_schematic: List[str]):
        if type(input_schematic) != list:
            raise AoC2023Day3Exception(
                "%s: %s" % (INVALID_TYPE_EXCEPTION, type(input_schematic))
            )

        # Finding numbers and their start and end position in the current line and all symbols start and end positions
        # Ensure the correct entry is selected from the regex using count with sub_found_part_symbols and
        # line_found_part_numbers
        for i in range(len(input_schematic)):
            line_number_start_indices: List[int] = []
            line_number_end_indices: List[int] = []
            line_symbol_start_indices: List[int] = []
            line_found_part_numbers: List[int] = []
            sub_found_part_symbols: List[str] = []

            current_line = input_schematic[i]

            numbers_in_line = NUMBER_REGEX_PATTERN.findall(current_line)

            for num in numbers_in_line:
                line_found_part_numbers.append(int(num))
                line_number_start_indices.append(
                    list(re.finditer(r"(?<!\d){}(?!\d)".format(num), current_line))[
                        line_found_part_numbers.count(int(num)) - 1
                    ].start()
                )
                line_number_end_indices.append(
                    list(re.finditer(r"(?<!\d){}(?!\d)".format(num), current_line))[
                        line_found_part_numbers.count(int(num)) - 1
                    ].end()
                )

            symbol_search = SYMBOL_REGEX_PATTERN.findall(current_line)
            for sym in symbol_search:
                if sym == self._period or sym == self._newline:
                    continue
                sub_found_part_symbols.append(sym)
                line_symbol_start_indices.append(
                    list(re.finditer(re.escape(sym), current_line))[
                        sub_found_part_symbols.count(sym) - 1
                    ].start()
                )

            self._number_start_indices.append(line_number_start_indices)
            self._number_end_indices.append(line_number_end_indices)
            self._symbol_start_indices.append(line_symbol_start_indices)
            self._found_numbers_list.append(line_found_part_numbers)

        # Check if numbers are adjacent to symbols horizontally, vertically, or diagonally in the current,
        # previous, and next rows
        for row, (
            sub_numbers,
            sub_number_start_index,
            sub_number_end_index,
        ) in enumerate(
            zip(
                self._found_numbers_list,
                self._number_start_indices,
                self._number_end_indices,
            )
        ):
            self._find_part_numbers(
                sub_numbers, sub_number_start_index, sub_number_end_index, row
            )

        self._sum_part_numbers = sum(self._found_part_numbers)

    @staticmethod
    def _is_within_range(start: int, value: int, end: int):
        return start - 1 <= value <= end + 1

    def _check_range_and_append(
        self, symbol_start: int, number_start: int, number_end: int, number: int
    ):
        if self._is_within_range(
            symbol_start, number_start, symbol_start
        ) or self._is_within_range(symbol_start, number_end - 1, symbol_start):
            self._found_part_numbers.append(number)
            return True
        return False

    def _find_part_numbers(
        self,
        sub_numbers: List[int],
        sub_number_start_index: List[int],
        sub_number_end_index: List[int],
        row: int,
    ):
        if row == 0:
            search_range = [0, 1]
        elif row + 1 == len(self._symbol_start_indices):
            search_range = [row - 1, row]
        else:
            search_range = [row - 1, row, row + 1]

        for number, number_start, number_end in zip(
            sub_numbers, sub_number_start_index, sub_number_end_index
        ):
            for i in search_range:
                for symbol_start in self._symbol_start_indices[i]:
                    if self._check_range_and_append(
                        symbol_start, number_start, number_end, number
                    ):
                        break
            else:
                continue

    def get_sum_part_numbers(self) -> int:
        return self._sum_part_numbers

    def get_found_part_ids(self) -> List[int]:
        return self._found_part_numbers


if __name__ == "__main__":

    day3_file_path = os.path.abspath("../../test/input_data/2023/day3_input.txt")
    if not os.path.exists(day3_file_path):
        raise FileNotFoundError(f"File not found: {day3_file_path}")

    day3 = Day3()

    try:
        with open(day3_file_path, "r") as input_file:
            input_schematic_data = input_file.readlines()

            if not input_schematic_data:
                raise AoC2023Day3Exception("Input schematic is empty")

            day3.search_schematic(input_schematic_data)
    except OSError as e:
        raise AoC2023Day3Exception(f"Error reading file: {e}")

    print("--- Day 3: Gear Ratios ---")
    print(
        f"Part A Sum of all of the found part numbers value: {day3.get_sum_part_numbers()}"
    )
    # print("Part B Sum of all of the cube power values: %d" % day2.get_sum_cube_power())
