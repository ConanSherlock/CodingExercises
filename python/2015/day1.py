import enum

INVALID_TYPE_EXCEPTION = "Invalid data type given"
INVALID_CHAR_EXCEPTION = "Invalid character given"

BASEMENT_NOT_FOUND = -1


# Expected Character enum
class Directions(enum.Enum):
    UP = "("
    DOWN = ")"


class AoC2015Day1Exception(Exception):
    def __init__(self, value):
        self.value = value

    def __str__(self):
        return repr(self.value)


class Day1:
    def __init__(self):
        self._floor = 0
        self._basement_interation_index = BASEMENT_NOT_FOUND

    def reset(self):
        self._floor = 0
        self._basement_interation_index = BASEMENT_NOT_FOUND

    def calc_floor(self, input_string):
        # Checking for invalid input types
        if type(input_string) != str:
            raise AoC2015Day1Exception("%s: %s" % (INVALID_TYPE_EXCEPTION, type(input_string)))

        loop_count = 0

        for character in input_string:
            if character != Directions.UP.value and character != Directions.DOWN.value:
                raise AoC2015Day1Exception("%s: %s" % (INVALID_CHAR_EXCEPTION, character))

            if character == Directions.UP.value:
                self._floor += 1
            elif character == Directions.DOWN.value:
                self._floor -= 1

            # Setting basement interation only if it not already found
            if self._floor < 0 and self._basement_interation_index == BASEMENT_NOT_FOUND:
                self._basement_interation_index = loop_count

            loop_count += 1

    def get_floor(self):
        return self._floor

    def get_basement_interation(self):
        # Adjusting for indexing to be 1 indexed instead of 0 indexed
        return self._basement_interation_index + 1


if __name__ == "__main__":

    day1_file_path = "../../test/input_data/2015/day1_input.txt"

    with open(day1_file_path, "r") as input_file:
        input_data = input_file.read()

    day1 = Day1()

    day1.calc_floor(input_data)

    print("--- Day 1: Not Quite Lisp ---")
    print("Part A Final floor: %d" % day1.get_floor())
    print("Part B Iterations until basement entered: %d" % day1.get_basement_interation())
