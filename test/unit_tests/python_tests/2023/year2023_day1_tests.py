import importlib
import unittest

# This script should be run from PathToRepo/test/unit_tests/python_tests/2023
# Try to general utils code
try:
    spec = importlib.util.spec_from_file_location(  # type: ignore
        "mod", "../../../../python/2023/day1.py"
    )
    day1 = importlib.util.module_from_spec(spec)  # type: ignore
    spec.loader.exec_module(day1)


except FileNotFoundError as e:
    print(e)
    print("Failed importing AoC 2023 day1")
    exit(-1)


class AoC2015Day1Test(unittest.TestCase):
    def setUp(self):
        self.__class__.day1 = None

    def test_given_inputs_calibration(self):
        self.__class__.day1 = day1.Day1()

        input_strings = ["1abc2", "pqr3stu8vwx", "a1b2c3d4e5f", "treb7uchet"]

        expected_calibration_outputs = [12, 38, 15, 77]

        expected_total_calibration = 142

        expected_init_total_calibration = 0
        expected_init_current_calibration = -1

        self.assertEqual(
            expected_init_total_calibration, self.__class__.day1.get_total_calibration()
        )
        self.assertEqual(
            expected_init_current_calibration,
            self.__class__.day1.get_current_calibration(),
        )

        for input_string, expected_calibration in zip(
            input_strings, expected_calibration_outputs
        ):
            self.__class__.day1.find_calibration(input_string)
            actual_calibration = self.__class__.day1.get_current_calibration()
            self.assertEqual(expected_calibration, actual_calibration)

        self.assertEqual(
            expected_total_calibration, self.__class__.day1.get_total_calibration()
        )

        self.__class__.day1.reset()
        self.assertEqual(
            expected_init_total_calibration, self.__class__.day1.get_total_calibration()
        )
        self.assertEqual(
            expected_init_current_calibration,
            self.__class__.day1.get_current_calibration(),
        )

    def test_given_inputs_basement_iteration(self):
        self.__class__.day1 = day1.Day1()

        input_strings = [")", "()())", "("]

        expected_basement_iteration_not_found = 0

        expected_basement_outputs = [1, 5, expected_basement_iteration_not_found]

        for input_string, expected_basement_output in zip(
            input_strings, expected_basement_outputs
        ):
            self.__class__.day1.reset()

            self.assertEqual(
                expected_basement_iteration_not_found,
                self.__class__.day1.get_basement_interation(),
            )

            self.__class__.day1.calc_floor(input_string)

            actual_basement_value = self.__class__.day1.get_basement_interation()

            self.assertEqual(expected_basement_output, actual_basement_value)

    def test_bad_inputs(self):
        self.__class__.day1 = day1.Day1()

        expected_bad_data_exception = "Invalid data type given"

        try:
            self.__class__.day1.find_calibration(1)
            self.assertTrue(False, "Exception not thrown")
        except day1.AoC2015Day1Exception as excep:
            self.assertTrue(expected_bad_data_exception in str(excep))
