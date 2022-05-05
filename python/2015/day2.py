import enum
import re

INVALID_TYPE_EXCEPTION = "Invalid data type given"
INVALID_STRING_COMPOSITION_EXCEPTION = "Invalid string composition given"


# Group numbers from Regex enum
class Dimensions(enum.Enum):
    LENGTH = 1
    WIDTH = 2
    HEIGHT = 3


class AoC2015Day2Exception(Exception):
    def __init__(self, value):
        self.value = value

    def __str__(self):
        return repr(self.value)


class Day2:
    def __init__(self):
        self._regex = re.compile(r'(\d+)x(\d+)x(\d+)')
        self._match = None
        self._length = -1
        self._width = -1
        self._height = -1
        self._paper_required = -1
        self._slack = -1
        self._total_paper_required = 0
        self._total_ribbon_required = 0

    def reset(self):
        self._regex = re.compile(r'(\d+)x(\d+)x(\d+)')
        self._match = None
        self._length = -1
        self._width = -1
        self._height = -1
        self._paper_required = -1
        self._slack = -1
        self._total_paper_required = 0
        self._total_ribbon_required = 0

    def calc_dimensions(self, input_string):
        # Checking for invalid input types
        if type(input_string) != str:
            raise AoC2015Day2Exception("%s: %s" % (INVALID_TYPE_EXCEPTION, type(input_string)))

        self._match = self._regex.match(input_string)

        if self._match is None:
            raise AoC2015Day2Exception("%s: %s" % (INVALID_STRING_COMPOSITION_EXCEPTION, input_string))

        self._length = int(self._match.group(Dimensions.LENGTH.value))
        self._width = int(self._match.group(Dimensions.WIDTH.value))
        self._height = int(self._match.group(Dimensions.HEIGHT.value))

        list_of_side_areas = [self._length*self._width, self._width*self._height, self._height*self._length]

        self._slack = min(list_of_side_areas)

        self._paper_required = 2 * self._length * self._width + \
            2 * self._width * self._height + \
            2 * self._height * self._length + self._slack

        self._total_paper_required += self._paper_required

    def get_total_paper_required(self):
        return self._total_paper_required

    def get_total_ribbon_required(self):
        return self._total_paper_required


if __name__ == "__main__":

    day2_file_path = "../../test/input_data/2015/day2_input.txt"

    with open(day2_file_path, "r") as input_file:
        input_data = input_file.readlines()

    day2 = Day2()

    for line in input_data:
        day2.calc_dimensions(line.strip("\n").strip("\r"))

    print("--- Day 2: I Was Told There Would Be No Math ---")
    print("Part A Wrapping Paper required: %d" % day2.get_total_paper_required())
    print("Part B Ribbon required: %d" % day2.get_total_ribbon_required())
