import re

INVALID_TYPE_EXCEPTION = "Invalid data type given"


class AoC2023Day2Exception(Exception):
    def __init__(self, value):
        self.value = value

    def __str__(self):
        return repr(self.value)


class Day2:
    def __init__(self):
        self._possible_configuration = False
        self._sum_game_ids = 0
        self._colour_regex_pattern = re.compile(
            r"(\d+)\s*green|(\d+)\s*red|(\d+)\s*blue"
        )
        self._game_regex_pattern = re.compile(r"Game (\d+):")
        self._green_limit = 13
        self._red_limit = 12
        self._blue_limit = 14
        self._necessary_green_cubes = 0
        self._necessary_red_cubes = 0
        self._necessary_blue_cubes = 0
        self._current_cube_power = 0
        self._sum_cube_power = 0

    def reset(self):
        self._possible_configuration = False
        self._sum_game_ids = 0
        self._necessary_green_cubes = 0
        self._necessary_red_cubes = 0
        self._necessary_blue_cubes = 0
        self._current_cube_power = 0
        self._sum_cube_power = 0

    def possible_configuration(self, input_string: str):
        # Checking for invalid input types
        if type(input_string) != str:
            raise AoC2023Day2Exception(
                "%s: %s" % (INVALID_TYPE_EXCEPTION, type(input_string))
            )

        self._possible_configuration = True

        game_id_search = self._game_regex_pattern.findall(input_string)

        colour_search = self._colour_regex_pattern.findall(input_string)
        green_list = []
        red_list = []
        blue_list = []
        over_max_green_list = []
        over_max_red_list = []
        over_max_blue_list = []

        for match in colour_search:
            green, red, blue = match

            # If Value Error match not found
            try:
                green_list.append(int(green))
                if green_list[-1] > self._green_limit:
                    over_max_green_list.append(int(green))
                    self._possible_configuration = False
            except ValueError:
                pass
            try:
                red_list.append(int(red))
                if red_list[-1] > self._red_limit:
                    over_max_red_list.append(int(red))
                    self._possible_configuration = False
            except ValueError:
                pass
            try:
                blue_list.append(int(blue))
                if blue_list[-1] > self._blue_limit:
                    over_max_blue_list.append(int(blue))
                    self._possible_configuration = False
            except ValueError:
                pass

        if self._possible_configuration:
            self._sum_game_ids += int(game_id_search[0])

        # Empty list if value error
        try:
            if len(over_max_green_list) > 0:
                self._necessary_green_cubes = max(over_max_green_list)
            else:
                self._necessary_green_cubes = max(green_list)
        except ValueError:
            self._necessary_green_cubes = 0
            pass
        try:
            if len(over_max_red_list) > 0:
                self._necessary_red_cubes = max(over_max_red_list)
            else:
                self._necessary_red_cubes = max(red_list)
        except ValueError:
            self._necessary_red_cubes = 0
            pass
        try:
            if len(over_max_blue_list) > 0:
                self._necessary_blue_cubes = max(over_max_blue_list)
            else:
                self._necessary_blue_cubes = max(blue_list)
        except ValueError:
            self._necessary_blue_cubes = 0
            pass

        self._current_cube_power = (
            self._necessary_green_cubes
            * self._necessary_red_cubes
            * self._necessary_blue_cubes
        )
        self._sum_cube_power += self._current_cube_power

    def get_sum_game_ids(self) -> int:
        return self._sum_game_ids

    def get_possible_configuration(self) -> bool:
        return self._possible_configuration

    def get_current_cube_power(self) -> int:
        return self._current_cube_power

    def get_sum_cube_power(self) -> int:
        return self._sum_cube_power


if __name__ == "__main__":

    day1_file_path = "../../test/input_data/2023/day2_input.txt"

    with open(day1_file_path, "r") as input_file:
        input_data = input_file.readlines()

    day2 = Day2()

    for game_input in input_data:
        day2.possible_configuration(game_input)

    print("--- Day 2: Cube Conundrum ---")
    print("Part A Sum of all of the found id values: %d" % day2.get_sum_game_ids())
    print("Part B Sum of all of the cube power values: %d" % day2.get_sum_cube_power())
