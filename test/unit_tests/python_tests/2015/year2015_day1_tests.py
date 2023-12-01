import importlib
import unittest

# This script should be run from PathToRep0/test/unit_tests/python_tests/2015
# Try to general utils code
try:
    spec = importlib.util.spec_from_file_location(  # type: ignore [attr-defined]
        "mod", "../../../../python/2015/day1.py"
    )  # type: ignore

    day1 = importlib.util.module_from_spec(spec)  # type: ignore [attr-defined]
    spec.loader.exec_module(day1)

except FileNotFoundError as e:
    print(e)
    print("Failed importing AoC 2015 day1")
    exit(-1)


class AoC2015Day1Test(unittest.TestCase):
    def setUp(self):
        self.__class__.day1 = None

    def test_given_inputs_floor_number(self):
        self.__class__.day1 = day1.Day1()

        input_strings = [
            "(())",
            "()()",
            "(((",
            "(()(()(",
            "))(((((",
            "())",
            "))(",
            ")))",
            ")())())",
        ]

        expected_floor_outputs = [0, 0, 3, 3, 3, -1, -1, -3, -3]

        expected_initial_floor = 0

        for input_string, expected_floor_output in zip(
            input_strings, expected_floor_outputs
        ):
            self.__class__.day1.reset()

            self.assertEqual(expected_initial_floor, self.__class__.day1.get_floor())

            self.__class__.day1.calc_floor(input_string)

            actual_floor = self.__class__.day1.get_floor()

            self.assertEqual(expected_floor_output, actual_floor)

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
        expected_bad_char_exception = "Invalid char"

        try:
            self.__class__.day1.calc_floor(1)
            self.assertTrue(False, "Exception not thrown")
        except day1.AoC2015Day1Exception as excep:
            self.assertTrue(expected_bad_data_exception in str(excep))

        try:
            self.__class__.day1.calc_floor("Lobster Thermidor and Spam")
            self.assertTrue(False, "Exception not thrown")
        except day1.AoC2015Day1Exception as excep:
            self.assertTrue(expected_bad_char_exception in str(excep))
