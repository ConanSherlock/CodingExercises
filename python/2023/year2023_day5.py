import re
import os
from typing import List, Tuple


class AoC2023Day5Exception(Exception):
    def __init__(self, value):
        self.value = value
        super().__init__(value)


class Day5:
    INVALID_TYPE_SELECTION = "Invalid data type given"
    NO_GROUPS_FOUND = "No groups found in search data"
    NUMBER_SEARCH_REGEX = re.compile(r"(\d+)")
    MAP_SEARCH_REGEX = re.compile(r"((\d+) (\d+) (\d+))")
    REGEX_MAP_TO_POSITION = 2
    REGEX_MAP_FROM_POSITION = 3
    REGEX_MAP_STEPS_POSITION = 4
    TUPLE_MAP_INITIAL_FROM_POSITION = 0
    TUPLE_MAP_FINAL_FROM_POSITION = 1
    TUPLE_MAP_INITIAL_TO_POSITION = 2
    TUPLE_MAP_FINAL_TO_POSITION = 3

    def __init__(self):
        self._seeds = []
        self._seed_to_soil_map = []
        self._seed_to_soil = False
        self._soil_to_fertilizer_map = []
        self._soil_to_fertilizer = False
        self._humidity_to_location_map = []
        self._humidity_to_location = False
        self._temperature_to_humidity_map = []
        self._temperature_to_humidity = False
        self._light_to_temperature_map = []
        self._light_to_temperature = False
        self._water_to_to_light_map = []
        self._water_to_to_light = False
        self._fertilizer_to_water_map = []
        self._fertilizer_to_water = False
        self._location_list = []
        self._map_line = False

    def reset(self):
        self._seeds.clear()
        self._seed_to_soil_map.clear()
        self._soil_to_fertilizer_map.clear()
        self._humidity_to_location_map.clear()
        self._temperature_to_humidity_map.clear()
        self._light_to_temperature_map.clear()
        self._water_to_to_light_map.clear()
        self._fertilizer_to_water_map.clear()
        self._location_list.clear()
        self._seed_to_soil = False
        self._soil_to_fertilizer = False
        self._humidity_to_location = False
        self._temperature_to_humidity = False
        self._light_to_temperature = False
        self._water_to_to_light = False
        self._fertilizer_to_water = False
        self._map_line = False

    def parse_almanac(self, almanac: List[str]):
        if not isinstance(almanac, list):
            raise AoC2023Day5Exception(
                f"{self.INVALID_TYPE_SELECTION}: {type(almanac)}"
            )
        else:
            for x in almanac:
                if not isinstance(x, str):
                    raise AoC2023Day5Exception(
                        f"{self.INVALID_TYPE_SELECTION} in list: {type(x)}"
                    )
        temp_map_to_nums: List[int] = []
        temp_map_from_nums: List[int] = []
        temp_map_steps: List[int] = []
        for line in almanac:
            if line == "\n":
                if (
                    not temp_map_to_nums == []
                    and not temp_map_from_nums == []
                    and not temp_map_steps == []
                ):
                    self._generate_map(
                        temp_map_to_nums, temp_map_from_nums, temp_map_steps
                    )
                    temp_map_to_nums.clear()
                    temp_map_from_nums.clear()
                    temp_map_steps.clear()
                continue
            if self._map_line:
                parsed_line = self.MAP_SEARCH_REGEX.match(line)
                if parsed_line is not None:
                    temp_map_to_nums.append(
                        int(parsed_line[self.REGEX_MAP_TO_POSITION])
                    )
                    temp_map_from_nums.append(
                        int(parsed_line[self.REGEX_MAP_FROM_POSITION])
                    )
                    temp_map_steps.append(
                        int(parsed_line[self.REGEX_MAP_STEPS_POSITION])
                    )
                else:
                    raise AoC2023Day5Exception("No match found")
                continue
            if "humidity-to-location map:" in line:
                self._humidity_to_location = True
                self._map_line = True
                continue
            if "temperature-to-humidity map:" in line:
                self._temperature_to_humidity = True
                self._map_line = True
                continue
            if "light-to-temperature map:" in line:
                self._light_to_temperature = True
                self._map_line = True
                continue
            if "water-to-light map:" in line:
                self._water_to_to_light = True
                self._map_line = True
                continue
            if "fertilizer-to-water map:" in line:
                self._fertilizer_to_water = True
                self._map_line = True
                continue
            if "soil-to-fertilizer map:" in line:
                self._soil_to_fertilizer = True
                self._map_line = True
                continue
            if "seed-to-soil map:" in line:
                self._seed_to_soil = True
                self._map_line = True
                continue
            if "seeds:" in line:
                self._populate_seeds_list(line)
                continue
        if any(
            x
            for x in [
                self._seed_to_soil,
                self._soil_to_fertilizer,
                self._humidity_to_location,
                self._temperature_to_humidity,
                self._light_to_temperature,
                self._water_to_to_light,
                self._fertilizer_to_water,
            ]
        ):
            if (
                not temp_map_to_nums == []
                and not temp_map_from_nums == []
                and not temp_map_steps == []
            ):
                self._generate_map(temp_map_to_nums, temp_map_from_nums, temp_map_steps)
                temp_map_to_nums.clear()
                temp_map_from_nums.clear()
                temp_map_steps.clear()

    def search_for_seed_location(self):
        for seed in self._seeds:
            temp_value = seed
            temp_value = self._map_value(self._seed_to_soil_map, temp_value)  # soil
            temp_value = self._map_value(
                self._soil_to_fertilizer_map, temp_value
            )  # fertilizer
            temp_value = self._map_value(
                self._fertilizer_to_water_map, temp_value
            )  # water
            temp_value = self._map_value(
                self._water_to_to_light_map, temp_value
            )  # light
            temp_value = self._map_value(
                self._light_to_temperature_map, temp_value
            )  # temperature
            temp_value = self._map_value(
                self._temperature_to_humidity_map, temp_value
            )  # humidity
            temp_value = self._map_value(
                self._humidity_to_location_map, temp_value
            )  # location
            self._location_list.append(temp_value)

    def search_for_seed_location_range_slow(self):
        seed_iter = iter(self._seeds)
        for seed in seed_iter:
            temp_start = seed
            temp_end = next(seed_iter)
            for i in range(temp_start, temp_end):
                temp_value = i
                temp_value = self._map_value(self._seed_to_soil_map, temp_value)  # soil
                temp_value = self._map_value(
                    self._soil_to_fertilizer_map, temp_value
                )  # fertilizer
                temp_value = self._map_value(
                    self._fertilizer_to_water_map, temp_value
                )  # water
                temp_value = self._map_value(
                    self._water_to_to_light_map, temp_value
                )  # light
                temp_value = self._map_value(
                    self._light_to_temperature_map, temp_value
                )  # temperature
                temp_value = self._map_value(
                    self._temperature_to_humidity_map, temp_value
                )  # humidity
                temp_value = self._map_value(
                    self._humidity_to_location_map, temp_value
                )  # location
                self._location_list.append(temp_value)

    def search_for_seed_location_seed_range(self):
        if len(self._seeds) % 2 != 0:
            raise AoC2023Day5Exception(
                "Total seed numbers is not even search_for_seed_location_seed_range cannot be used"
            )
        seed_iter = iter(self._seeds)
        for seed in seed_iter:
            temp_start = seed
            temp_end = seed + next(seed_iter) - 1

            # soil
            temp_range_info = self._map_range_values(
                self._seed_to_soil_map, [(temp_start, temp_end)]
            )
            print(temp_range_info)

            # fertilizer
            temp_range_info = self._map_range_values(
                self._soil_to_fertilizer_map, temp_range_info
            )
            print(temp_range_info)

            # water
            temp_range_info = self._map_range_values(
                self._fertilizer_to_water_map, temp_range_info
            )
            print(temp_range_info)

            # light
            temp_range_info = self._map_range_values(
                self._water_to_to_light_map, temp_range_info
            )
            print(temp_range_info)

            # temperature
            temp_range_info = self._map_range_values(
                self._light_to_temperature_map, temp_range_info
            )
            print(temp_range_info)

            # humidity
            temp_range_info = self._map_range_values(
                self._temperature_to_humidity_map, temp_range_info
            )
            print(temp_range_info)

            # location
            temp_range_info = self._map_range_values(
                self._humidity_to_location_map, temp_range_info
            )
            print(temp_range_info)

            for value_tuple in temp_range_info:
                self._location_list.append(value_tuple[0])

    def _map_value(
        self, current_map: List[Tuple[int, int, int, int]], current_value: int
    ) -> int:
        for mapping in current_map:
            if (
                mapping[self.TUPLE_MAP_INITIAL_FROM_POSITION]
                <= current_value
                <= mapping[self.TUPLE_MAP_FINAL_FROM_POSITION]
            ):
                current_value = (
                    current_value
                    - mapping[self.TUPLE_MAP_INITIAL_FROM_POSITION]
                    + mapping[self.TUPLE_MAP_INITIAL_TO_POSITION]
                )
                break
        return current_value

    def _map_range_values(
        self,
        current_map: List[Tuple[int, int, int, int]],
        values_list: List[Tuple[int, int]],
    ) -> List[Tuple[int, int]]:
        return_mapped_list = []
        # for value in values_list:
        pairs_to_check = values_list
        while pairs_to_check:
            current_pair = pairs_to_check.pop()

            for mapping in current_map:
                start_value_in_range = (
                    mapping[self.TUPLE_MAP_INITIAL_FROM_POSITION]
                    <= current_pair[0]
                    <= mapping[self.TUPLE_MAP_FINAL_FROM_POSITION]
                )
                end_value_in_range = (
                    mapping[self.TUPLE_MAP_INITIAL_FROM_POSITION]
                    <= current_pair[1]
                    <= mapping[self.TUPLE_MAP_FINAL_FROM_POSITION]
                )

                inner_start_range = (
                    current_pair[0]
                    <= mapping[self.TUPLE_MAP_INITIAL_FROM_POSITION]
                    <= current_pair[1]
                )
                inner_end_range = (
                    current_pair[0]
                    <= mapping[self.TUPLE_MAP_FINAL_FROM_POSITION]
                    <= current_pair[1]
                )

                if (
                    not start_value_in_range
                    and not end_value_in_range
                    and not inner_start_range
                    and not inner_end_range
                ):
                    continue

                if start_value_in_range and end_value_in_range:
                    start_value = (
                        current_pair[0]
                        - mapping[self.TUPLE_MAP_INITIAL_FROM_POSITION]
                        + mapping[self.TUPLE_MAP_INITIAL_TO_POSITION]
                    )
                    end_value = (
                        current_pair[1]
                        - mapping[self.TUPLE_MAP_INITIAL_FROM_POSITION]
                        + mapping[self.TUPLE_MAP_INITIAL_TO_POSITION]
                    )
                    return_mapped_list.append((start_value, end_value))
                    break
                elif start_value_in_range:
                    return_mapped_list.append(
                        (
                            current_pair[0]
                            - mapping[self.TUPLE_MAP_INITIAL_FROM_POSITION]
                            + mapping[self.TUPLE_MAP_INITIAL_TO_POSITION],
                            mapping[self.TUPLE_MAP_FINAL_TO_POSITION],
                        )
                    )
                    start_value = mapping[self.TUPLE_MAP_FINAL_FROM_POSITION]
                    if start_value != current_pair[1]:
                        pairs_to_check.append((start_value + 1, current_pair[1]))
                    break

                elif end_value_in_range:
                    return_mapped_list.append(
                        (
                            mapping[self.TUPLE_MAP_INITIAL_TO_POSITION],
                            current_pair[1]
                            - mapping[self.TUPLE_MAP_INITIAL_FROM_POSITION]
                            + mapping[self.TUPLE_MAP_INITIAL_TO_POSITION],
                        )
                    )
                    end_value = mapping[self.TUPLE_MAP_INITIAL_FROM_POSITION]

                    if current_pair[0] != end_value:
                        pairs_to_check.append((current_pair[0], end_value - 1))
                    break
                elif inner_start_range and inner_end_range:
                    return_mapped_list.append(
                        (
                            mapping[self.TUPLE_MAP_INITIAL_TO_POSITION],
                            mapping[self.TUPLE_MAP_FINAL_TO_POSITION] - 1,
                        )
                    )
                    if current_pair[0] != (
                        mapping[self.TUPLE_MAP_INITIAL_TO_POSITION] - 1
                    ):
                        pairs_to_check.append(
                            (
                                current_pair[0],
                                mapping[self.TUPLE_MAP_INITIAL_FROM_POSITION] - 1,
                            )
                        )

                    if current_pair[1] != (mapping[self.TUPLE_MAP_FINAL_TO_POSITION]):
                        pairs_to_check.append(
                            (
                                mapping[self.TUPLE_MAP_FINAL_FROM_POSITION] + 1,
                                current_pair[1],
                            )
                        )
                    break
            else:
                return_mapped_list.append((current_pair[0], current_pair[1]))

        return_mapped_list.sort()
        return return_mapped_list

    def _populate_seeds_list(self, line: str):
        self._seeds = [int(x) for x in self.NUMBER_SEARCH_REGEX.findall(line)]

    def _generate_map(
        self,
        temp_map_to_nums: List[int],
        temp_map_from_nums: List[int],
        temp_map_steps: List[int],
    ):
        temp_map = []
        for from_num, steps, to_num in zip(
            temp_map_from_nums, temp_map_steps, temp_map_to_nums
        ):
            temp_map.append(
                (from_num, from_num + steps - 1, to_num, to_num + steps - 1)
            )
        if self._seed_to_soil:
            self._seed_to_soil_map = temp_map.copy()
            self._seed_to_soil = False
        if self._soil_to_fertilizer:
            self._soil_to_fertilizer_map = temp_map.copy()
            self._soil_to_fertilizer = False
        if self._fertilizer_to_water:
            self._fertilizer_to_water_map = temp_map.copy()
            self._fertilizer_to_water = False
        if self._water_to_to_light:
            self._water_to_to_light_map = temp_map.copy()
            self._water_to_to_light = False
        if self._light_to_temperature:
            self._light_to_temperature_map = temp_map.copy()
            self._light_to_temperature = False
        if self._temperature_to_humidity:
            self._temperature_to_humidity_map = temp_map.copy()
            self._temperature_to_humidity = False
        if self._humidity_to_location:
            self._humidity_to_location_map = temp_map.copy()
            self._humidity_to_location = False
        self._map_line = False

    def get_lowest_location(self) -> int:
        try:
            return min(self._location_list)
        except ValueError:
            return -1


if __name__ == "__main__":
    day5_file_path = os.path.abspath("../../test/input_data/2023/day5_input.txt")
    if not os.path.exists(day5_file_path):
        raise FileNotFoundError(f"File not found: {day5_file_path}")
    day5 = Day5()
    try:
        with open(day5_file_path, "r") as input_file:
            island_island_almanac = input_file.readlines()
            if not island_island_almanac:
                raise AoC2023Day5Exception("The almanac is empty")
            day5.parse_almanac(island_island_almanac)
            day5.search_for_seed_location()
    except OSError as e:
        raise AoC2023Day5Exception(f"Error reading file: {e}")

    print("--- Day 5: If You Give A Seed A Fertilizer ---")
    print(
        f"Part A Lowest location number based on initial seed numbers: {day5.get_lowest_location()}"
    )
    day5.reset()
    try:
        with open(day5_file_path, "r") as input_file:
            island_island_almanac = input_file.readlines()
            if not island_island_almanac:
                raise AoC2023Day5Exception("The almanac is empty")
            day5.parse_almanac(island_island_almanac)
            day5.search_for_seed_location_seed_range()
    except OSError as e:
        raise AoC2023Day5Exception(f"Error reading file: {e}")
    print(
        f"Part B Lowest location number based on initial seed numbers range: {day5.get_lowest_location()}"
    )
