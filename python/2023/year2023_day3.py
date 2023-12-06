import re
import os
from typing import List


class AoC2023Day3Exception(Exception):
    def __init__(self, value):
        self.value = value
        super().__init__(value)


class Day3:
    PERIOD = "."
    GEAR_SYMBOL = "*"
    NEWLINE = "\n"
    INVALID_TYPE_SELECTION = "Invalid data type given"
    NUMBER_REGEX_PATTERN = re.compile(r"(\d+)")
    SYMBOL_REGEX_PATTERN = re.compile(r"[^a-zA-Z0-9]")
    _number_start_indices: List[List[int]]
    _number_end_indices: List[List[int]]
    _symbol_start_indices: List[List[int]]
    _found_part_numbers: List[int]
    _found_numbers_list: List[List[int]]
    _found_gear_numbers_list: List[List[int]]
    _sum_part_numbers: int
    _sum_gear_ratio: int

    def __init__(self):
        self._number_start_indices = []
        self._number_end_indices = []
        self._symbol_start_indices = []
        self._found_part_numbers = []
        self._found_numbers_list = []
        self._found_symbols_list = []
        self._found_gear_numbers_list = []
        self._sum_part_numbers = 0
        self._sum_gear_ratio = 0

    def reset(self):
        self._number_start_indices.clear()
        self._number_end_indices.clear()
        self._symbol_start_indices.clear()
        self._found_part_numbers.clear()
        self._found_numbers_list.clear()
        self._found_symbols_list.clear()
        self._found_gear_numbers_list.clear()
        self._sum_part_numbers = 0
        self._sum_gear_ratio = 0

    def search_schematic(self, input_schematic: List[str]):
        """Search the schematic for part numbers."""
        if not isinstance(input_schematic, list):
            raise AoC2023Day3Exception(
                f"{self.INVALID_TYPE_SELECTION}: {type(input_schematic)}"
            )
        for current_line in input_schematic:
            (
                line_number_start_indices,
                line_number_end_indices,
                line_found_part_numbers,
            ) = self.find_numbers_in_line(current_line)
            (
                line_symbol_start_indices,
                sub_found_part_symbols,
            ) = self.find_symbols_in_line(current_line)
            self._number_start_indices.append(line_number_start_indices)
            self._number_end_indices.append(line_number_end_indices)
            self._symbol_start_indices.append(line_symbol_start_indices)
            self._found_numbers_list.append(line_found_part_numbers)
            self._found_symbols_list.append(sub_found_part_symbols)
        self.calculate_sum_of_symbol_adjacent_numbers()
        self.calculate_sum_of_gear_ratios()

    def find_numbers_in_line(self, current_line: str):
        """Find numbers and their start and end positions in a line."""
        line_number_start_indices: List[int] = []
        line_number_end_indices: List[int] = []
        line_found_part_numbers: List[int] = []
        numbers_in_line = self.NUMBER_REGEX_PATTERN.findall(current_line)
        for num in numbers_in_line:
            line_found_part_numbers.append(int(num))
            current_number_regex = r"(?<!\d){}(?!\d)".format(num)
            line_number_start_indices.append(
                list(re.finditer(current_number_regex, current_line))[
                    line_found_part_numbers.count(int(num)) - 1
                ].start()
            )
            line_number_end_indices.append(
                list(re.finditer(current_number_regex, current_line))[
                    line_found_part_numbers.count(int(num)) - 1
                ].end()
            )
        return (
            line_number_start_indices,
            line_number_end_indices,
            line_found_part_numbers,
        )

    def find_symbols_in_line(self, current_line: str):
        """Find symbols and their start positions in a line."""
        line_symbol_start_indices: List[int] = []
        sub_found_part_symbols: List[str] = []
        symbol_search = self.SYMBOL_REGEX_PATTERN.findall(current_line)
        for sym in symbol_search:
            if sym == self.PERIOD or sym == self.NEWLINE:
                continue
            sub_found_part_symbols.append(sym)
            line_symbol_start_indices.append(
                list(re.finditer(re.escape(sym), current_line))[
                    sub_found_part_symbols.count(sym) - 1
                ].start()
            )
        return line_symbol_start_indices, sub_found_part_symbols

    def calculate_sum_of_symbol_adjacent_numbers(self):
        """Check if numbers are adjacent to symbols and calculate the sum."""
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

    def calculate_sum_of_gear_ratios(self):
        """Check if numbers are adjacent to symbols and calculate the sum."""
        for row, (sub_symbols, sub_symbol_start_index,) in enumerate(
            zip(
                self._found_symbols_list,
                self._symbol_start_indices,
            )
        ):
            self._find_gear_ratios(sub_symbols, sub_symbol_start_index, row)
        for gear_numbers in self._found_gear_numbers_list:
            self._sum_gear_ratio = self._sum_gear_ratio + (
                gear_numbers[0] * gear_numbers[1]
            )

    @staticmethod
    def _is_within_range(start: int, value: int, end: int):
        return start - 1 <= value <= end + 1

    def _check_range_and_append_number(
        self, symbol_start: int, number_start: int, number_end: int, number: int
    ):
        if self._is_within_range(
            symbol_start, number_start, symbol_start
        ) or self._is_within_range(symbol_start, number_end - 1, symbol_start):
            self._found_part_numbers.append(number)
            return True
        return False

    def _check_range_and_append_gear(
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
                    if self._check_range_and_append_number(
                        symbol_start, number_start, number_end, number
                    ):
                        break
            else:
                continue

    def _find_gear_ratios(
        self, sub_symbols: List[str], sub_symbol_start_index: List[int], row: int
    ):
        if row == 0:
            search_range = [0, 1]
        elif row + 1 == len(self._symbol_start_indices):
            search_range = [row - 1, row]
        else:
            search_range = [row - 1, row, row + 1]
        for symbol, symbol_start in zip(sub_symbols, sub_symbol_start_index):
            if symbol not in self.GEAR_SYMBOL:
                continue
            self._find_gear_numbers(search_range, symbol_start)

    def _find_gear_numbers(self, search_range: List[int], symbol_start: int):
        found_gear_numbers = []
        for i in search_range:
            for number_start, number_end, number in zip(
                self._number_start_indices[i],
                self._number_end_indices[i],
                self._found_numbers_list[i],
            ):
                # Adjusting number_end by -1 to align with 0 indexing
                if self._is_within_range(number_start, symbol_start, number_end - 1):
                    found_gear_numbers.append(number)
        if len(found_gear_numbers) == 2:
            self._found_gear_numbers_list.append(found_gear_numbers)

    def get_sum_part_numbers(self) -> int:
        return self._sum_part_numbers

    def get_sum_gear_ratio(self) -> int:
        return self._sum_gear_ratio

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
    print(f"Part B Sum of all of the gear ratio values: {day3.get_sum_gear_ratio()}")
