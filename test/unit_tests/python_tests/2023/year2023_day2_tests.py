import importlib
import unittest

# This script should be run from PathToRepo/test/unit_tests/python_tests/2023
# Try to general utils code
try:
    spec = importlib.util.spec_from_file_location(  # type: ignore
        "mod", "../../../../python/2023/year2023_day2.py"
    )
    day2 = importlib.util.module_from_spec(spec)  # type: ignore
    spec.loader.exec_module(day2)

except FileNotFoundError as e:
    print(e)
    print("Failed importing AoC 2023 day2")
    exit(-1)


class AoC2023Day2Test(unittest.TestCase):
    def setUp(self):
        self.__class__.day2 = None

    def test_given_inputs_calibration(self):
        self.__class__.day2 = day2.Day2()

        input_strings = [
            "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green\n",
            "Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue\n",
            "Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red\n",
            "Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red\n",
            "Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green\n",
        ]

        expected_possible_configurations = [True, True, False, False, True]

        expected_sum_id = 8

        expected_init_possible_configuration = False
        expected_init_expected_sum_id = 0

        self.assertEqual(
            expected_init_possible_configuration,
            self.__class__.day2.get_possible_configuration(),
        )
        self.assertEqual(
            expected_init_expected_sum_id, self.__class__.day2.get_sum_game_ids()
        )

        for input_string, expected_configurations in zip(
            input_strings, expected_possible_configurations
        ):
            self.__class__.day2.possible_configuration(input_string)
            actual_configuration = self.__class__.day2.get_possible_configuration()
            self.assertEqual(expected_configurations, actual_configuration)

        self.assertEqual(expected_sum_id, self.__class__.day2.get_sum_game_ids())

        self.__class__.day2.reset()
        self.assertEqual(
            expected_init_possible_configuration,
            self.__class__.day2.get_possible_configuration(),
        )
        self.assertEqual(
            expected_init_expected_sum_id, self.__class__.day2.get_sum_game_ids()
        )

    def test_given_inputs_advanced_calibration(self):
        self.__class__.day2 = day2.Day2()

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
        expected_sum_cube_powers = 0

        self.assertEqual(
            expected_init_cube_powers, self.__class__.day2.get_possible_configuration()
        )
        self.assertEqual(
            expected_sum_cube_powers, self.__class__.day2.get_sum_game_ids()
        )

        for input_string, expected_cube_power in zip(
            input_strings, expected_cube_powers
        ):
            self.__class__.day2.possible_configuration(input_string)
            self.__class__.day2.get_possible_configuration()
            self.assertEqual(
                expected_cube_power, self.__class__.day2.get_current_cube_power()
            )

        self.assertEqual(
            expected_sum_cube_powers, self.__class__.day2.get_sum_cube_power()
        )

        self.__class__.day2.reset()
        self.assertEqual(
            expected_init_cube_powers, self.__class__.day2.get_current_cube_power()
        )
        self.assertEqual(
            expected_sum_cube_powers, self.__class__.day2.get_sum_cube_power()
        )

    def test_bad_inputs(self):
        self.__class__.day2 = day2.Day2()

        expected_bad_data_exception = "Invalid data type given"

        try:
            self.__class__.day2.find_calibration(1)
            self.assertTrue(False, "Exception not thrown")
        except day2.AoC2023Day2Exception as excep:
            self.assertTrue(expected_bad_data_exception in str(excep))
