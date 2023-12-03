import importlib
import unittest

# This script should be run from PathToRepo/test/unit_tests/python_tests/2023
# Try to general utils code
try:
    spec = importlib.util.spec_from_file_location(  # type: ignore
        "mod", "../../../../python/2023/year2023_day3.py"
    )
    day3 = importlib.util.module_from_spec(spec)  # type: ignore
    spec.loader.exec_module(day3)

except FileNotFoundError as e:
    print(e)
    print("Failed importing AoC 2023 day3")
    exit(-1)


class AoC2023Day3Test(unittest.TestCase):
    def setUp(self):
        self.__class__.day3 = None

    def test_given_inputs_calibration(self):
        self.__class__.day3 = day3.Day3()

        input_strings = [
            "467..114..\n",
            "...*......\n",
            "..35..633.\n",
            "......#...\n",
            "617*......\n",
            "467..114..\n",
            ".....+.58.\n",
            "..592.....\n",
            "......755.\n",
            "...$.*....\n",
            ".664.598..\n",
        ]

        expected_found_part_ids_list = [
            [467],
            [],
            [35, 633],
            [],
            [617],
            [467, 114],
            [],
            [592],
            [755],
            [],
            [664, 598],
        ]

        expected_sum_parts_ids = 4361

        expected_init_found_part_ids = []
        expected_init_expected_sum_parts_ids = 0

        self.assertEqual(
            expected_init_found_part_ids,
            self.__class__.day3.get_found_part_ids(),
        )
        self.assertEqual(
            expected_init_expected_sum_parts_ids,
            self.__class__.day3.get_sum_part_numbers(),
        )

        self.__class__.day3.search_schematic(input_strings)
        actual_part_ids_list = self.__class__.day3.get_found_part_ids()

        self.assertEqual(len(expected_found_part_ids_list), len(actual_part_ids_list))
        for expected_part_ids, actual_part_ids in zip(
            expected_found_part_ids_list, actual_part_ids_list
        ):
            self.assertEqual(expected_part_ids, actual_part_ids)

        self.assertEqual(
            expected_sum_parts_ids, self.__class__.day3.get_sum_part_numbers()
        )

        self.__class__.day3.reset()
        self.assertEqual(
            expected_init_found_part_ids,
            self.__class__.day3.get_found_part_ids(),
        )
        self.assertEqual(
            expected_init_expected_sum_parts_ids,
            self.__class__.day3.get_sum_part_numbers(),
        )

    def test_given_inputs_advanced_calibration(self):
        self.__class__.day3 = day3.Day3()

        input_strings = [
            "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green\n",
            "Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue\n",
            "Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red\n",
            "Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red\n",
            "Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green\n",
        ]

        expected_cube_powers = [48, 12, 1560, 630, 36]

        expected_sum_cube_powers = 2286

        expected_init_cube_powers = 0
        expected_init_sum_cube_powers = 0

        self.assertEqual(
            expected_init_cube_powers, self.__class__.day3.get_found_part_ids()
        )
        self.assertEqual(
            expected_init_sum_cube_powers, self.__class__.day3.get_sum_part_numbers()
        )

        for input_string, expected_cube_power in zip(
            input_strings, expected_cube_powers
        ):
            self.__class__.day3.possible_configuration(input_string)
            self.assertEqual(
                expected_cube_power, self.__class__.day3.get_current_cube_power()
            )

        self.assertEqual(
            expected_sum_cube_powers, self.__class__.day3.get_sum_cube_power()
        )

        self.__class__.day3.reset()
        self.assertEqual(
            expected_init_cube_powers, self.__class__.day3.get_current_cube_power()
        )
        self.assertEqual(
            expected_init_sum_cube_powers, self.__class__.day3.get_sum_cube_power()
        )

    def test_bad_inputs(self):
        self.__class__.day3 = day3.Day3()

        expected_bad_data_exception = "Invalid data type given"

        try:
            self.__class__.day3.find_calibration(1)
            self.assertTrue(False, "Exception not thrown")
        except day3.AoC2023Day3Exception as excep:
            self.assertTrue(expected_bad_data_exception in str(excep))
