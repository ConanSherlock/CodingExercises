INVALID_TYPE_EXCEPTION = "Invalid data type given"


class AoC2015Day1Exception(Exception):
    def __init__(self, value):
        self.value = value

    def __str__(self):
        return repr(self.value)


class Day1:
    def __init__(self):
        self._get_total_calibration = 0
        self._current_calibration = -1

    def reset(self):
        self._get_total_calibration = 0
        self._current_calibration = -1


    def find_calibration(self, input_string):
        # Checking for invalid input types
        if type(input_string) != str:
            raise AoC2015Day1Exception("%s: %s" % (INVALID_TYPE_EXCEPTION, type(input_string)))

        self._current_calibration = -1

        found_digits = []

        for character in input_string:
            try:
                found_digits.append(int(character))
            except ValueError:
                # Ignore not a number
                pass

        if len(found_digits) > 1:
            found_number = found_digits[0] * 10 + found_digits[-1]
        elif len(found_digits) == 1:
            found_number = found_digits[0] * 10 + found_digits[0]
        else:
            found_number = 0

        self._current_calibration = found_number
        self._get_total_calibration += self._current_calibration

    def get_total_calibration(self):
        return self._get_total_calibration

    def get_current_calibration(self):
        return self._current_calibration


if __name__ == "__main__":

    day1_file_path = "../../test/input_data/2023/day1_input.txt"

    with open(day1_file_path, "r") as input_file:
        input_data = input_file.readlines()

    day1 = Day1()

    for calibration_input in input_data:
        day1.find_calibration(calibration_input)

    print("--- Day 1: Trebuchet?! ---")
    print("Part A Sum of all of the calibration values: %d" % day1.get_total_calibration())
    print("Part B Sum of all of the calibration values: %d" % day1.get_basement_interation())
