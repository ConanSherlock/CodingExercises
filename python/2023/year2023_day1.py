from typing import List, Dict

INVALID_TYPE_EXCEPTION = "Invalid data type given"


class AoC2023Day1Exception(Exception):
    def __init__(self, value):
        self.value = value

    def __str__(self):
        return repr(self.value)


NUMBER_DICT = {
    "zero": 0,
    "one": 1,
    "two": 2,
    "three": 3,
    "four": 4,
    "five": 5,
    "six": 6,
    "seven": 7,
    "eight": 8,
    "nine": 9,
}


class Day1:
    def __init__(self):
        self._get_total_calibration = 0
        self._current_calibration = -1

    def reset(self):
        self._get_total_calibration = 0
        self._current_calibration = -1

    def find_calibration(self, input_string: str, advanced_calibration: bool = False):

        if type(input_string) != str:
            raise AoC2023Day1Exception(
                "%s: %s" % (INVALID_TYPE_EXCEPTION, type(input_string))
            )

        self._current_calibration = -1

        found_digits = []
        found_digits_loc = []

        for location, character in enumerate(input_string):
            try:
                found_digits.append(int(character))
                found_digits_loc.append(location)
            except ValueError:
                # Ignore not a number
                pass

        found_named_digits_start = {}
        found_named_digits_end = {}

        for key in NUMBER_DICT:
            start_loc = input_string.find(key)
            end_loc = input_string.rfind(key)

            if start_loc >= 0 and end_loc >= 0:
                found_named_digits_start.update({key: start_loc})
                found_named_digits_end.update({key: end_loc})

        if advanced_calibration:
            found_number = self._create_advanced_found_number(
                found_digits,
                found_digits_loc,
                found_named_digits_start.copy(),
                found_named_digits_end.copy(),
            )
        else:
            found_number = self._create_found_number(found_digits)

        self._update_calibration(found_number)

    @staticmethod
    def _create_found_number(found_digits: List[int]) -> int:
        if len(found_digits) > 1:
            found_number = found_digits[0] * 10 + found_digits[-1]
        elif len(found_digits) == 1:
            found_number = found_digits[0] * 10 + found_digits[0]
        else:
            found_number = 0

        return found_number

    @staticmethod
    def _create_advanced_found_number(
        found_digits: List[int],
        found_digits_loc: List[int],
        found_named_digits_start: Dict[str, int],
        found_named_digits_end: Dict[str, int],
    ) -> int:
        if len(found_digits) == 0:
            first_digit_loc = -1
            last_digit_loc = -1
            first_digit = 0
            last_digit = 0
        else:
            first_digit_loc = found_digits_loc[0]
            last_digit_loc = found_digits_loc[-1]
            first_digit = found_digits[0]
            last_digit = found_digits[-1]

        for found_named_digit in found_named_digits_start.keys():
            if first_digit_loc < 0:
                first_digit = NUMBER_DICT[found_named_digit]
                first_digit_loc = found_named_digits_start[found_named_digit]
            elif found_named_digits_start[found_named_digit] < first_digit_loc:
                first_digit = NUMBER_DICT[found_named_digit]
                first_digit_loc = found_named_digits_start[found_named_digit]

            if last_digit_loc < 0:
                last_digit = NUMBER_DICT[found_named_digit]
                last_digit_loc = found_named_digits_end[found_named_digit]
            elif found_named_digits_end[found_named_digit] > last_digit_loc:
                last_digit = NUMBER_DICT[found_named_digit]
                last_digit_loc = found_named_digits_end[found_named_digit]

        found_number = first_digit * 10 + last_digit

        return found_number

    def _update_calibration(self, found_number: int):
        self._current_calibration = found_number
        self._get_total_calibration += self._current_calibration

    def get_total_calibration(self) -> int:
        return self._get_total_calibration

    def get_current_calibration(self) -> int:
        return self._current_calibration


if __name__ == "__main__":

    day1_file_path = "../../test/input_data/2023/day1_input.txt"

    with open(day1_file_path, "r") as input_file:
        input_data = input_file.readlines()

    day1 = Day1()

    for calibration_input in input_data:
        day1.find_calibration(calibration_input)

    print("--- Day 1: Trebuchet?! ---")
    print(
        "Part A Sum of all of the calibration values: %d" % day1.get_total_calibration()
    )

    day1.reset()
    for calibration_input in input_data:
        day1.find_calibration(calibration_input, True)
    print(
        "Part B Sum of all of the calibration values: %d" % day1.get_total_calibration()
    )
