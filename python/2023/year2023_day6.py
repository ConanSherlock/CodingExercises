import re
import os
from typing import List


class AoC2023Day6Exception(Exception):
    def __init__(self, value):
        self.value = value
        super().__init__(value)


class Day6:
    INVALID_TYPE_SELECTION = "Invalid data type given"
    NO_GROUPS_FOUND = "No groups found in search data"
    PARSING_REGEX = re.compile(r"(\d+)")
    ACCELERATION_MS = 1

    def __init__(self):
        self._races_point_value = 0

    def reset(self):
        self._races_point_value = 0

    def parse_race_info_multiple_races(self, race_info: List[str]):
        time_search_match = []
        distance_search_match = []

        for line in race_info:
            if "Time".lower() in line.lower():
                time_search_match = self.PARSING_REGEX.findall(line)
            if "Distance".lower() in line.lower():
                distance_search_match = self.PARSING_REGEX.findall(line)

        if not time_search_match:
            raise AoC2023Day6Exception("No matches found for Time:")
        if not distance_search_match:
            raise AoC2023Day6Exception("No matches found for Distance:")

        for time, distance in zip(time_search_match, distance_search_match):
            time = int(time)
            distance = int(distance)
            winning_combos = 0

            for i in range(0, time):
                if distance == 0 and time == 0:
                    winning_combos += 1
                    continue
                elif i == 0:
                    continue
                else:
                    if distance / i < (time - i):
                        winning_combos += 1

            if self._races_point_value == 0:
                self._races_point_value = winning_combos
            else:
                self._races_point_value *= winning_combos

        return

    def parse_race_info_single_race(self, race_info: List[str]):
        time_search_match = []
        distance_search_match = []

        for line in race_info:
            if "Time".lower() in line.lower():
                time_search_match = self.PARSING_REGEX.findall(line)
            if "Distance".lower() in line.lower():
                distance_search_match = self.PARSING_REGEX.findall(line)

        if not time_search_match:
            raise AoC2023Day6Exception("No matches found for Time:")
        if not distance_search_match:
            raise AoC2023Day6Exception("No matches found for Distance:")

        total_time = 0
        total_distance = 0
        winning_combos = 0

        for time, distance in zip(time_search_match, distance_search_match):
            time = int(time)
            distance = int(distance)

            if total_time == 0:
                total_time = time
            else:
                time_digits = self._find_digit_count_int(time)
                total_time = time + total_time * (pow(10, time_digits))

            if total_distance == 0:
                total_distance = distance
            else:
                distance_digits = self._find_digit_count_int(distance)
                total_distance = distance + total_distance * (pow(10, distance_digits))

        for i in range(0, total_time):
            if total_distance == 0 and total_time == 0:
                winning_combos += 1
                continue
            elif i == 0:
                continue
            else:
                if total_distance / i < (total_time - i):
                    winning_combos += 1

        self._races_point_value = winning_combos
        return

    @staticmethod
    def _find_digit_count_int(number: int) -> int:
        return len(str(number))

    def get_races_point_value(self) -> int:
        return self._races_point_value


if __name__ == "__main__":
    day6_file_path = os.path.abspath("../../test/input_data/2023/day6_input.txt")

    if not os.path.exists(day6_file_path):
        raise FileNotFoundError(f"File not found: {day6_file_path}")

    day6 = Day6()

    try:
        with open(day6_file_path, "r") as input_file:
            input_race_info = input_file.readlines()

            if not input_race_info:
                raise AoC2023Day6Exception("The race info is empty")

            day6.parse_race_info_multiple_races(input_race_info)

    except OSError as e:
        raise AoC2023Day6Exception(f"Error reading file: {e}")

    print("--- Day 6: Wait For It ---")
    print(
        f"Part A Point value of all race wins multiplied: {day6.get_races_point_value()}"
    )

    day6.reset()

    try:
        with open(day6_file_path, "r") as input_file:
            input_race_info = input_file.readlines()

            if not input_race_info:
                raise AoC2023Day6Exception("The race info is empty")

            day6.parse_race_info_single_race(input_race_info)

    except OSError as e:
        raise AoC2023Day6Exception(f"Error reading file: {e}")

    print(
        f"Part A Point value of all race wins multiplied: {day6.get_races_point_value()}"
    )
