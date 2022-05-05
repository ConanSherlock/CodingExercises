import importlib
import unittest

# This script should be run from PathToRepo/sonic/python/tools
# Try to general utils code
try:
    spec = importlib.util.spec_from_file_location("mod", "../../../python/2015/day2.py")

    day2 = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(day2)

except FileNotFoundError as e:
    print(e)
    print("Failed importing AoC 2015 day1")
    exit(-1)


class AoC2015Day1Test(unittest.TestCase):
    def setUp(self):
        self.__class__.day2 = None

    def test_given_inputs_part1(self):
        self.__class__.day2 = day2.Day2()

        input_strings = ["2x3x4", "1x1x10"]

        expected_sqr_ft_of_paper = [58, 43]

        expected_initial_sqr_ft_of_paper = 0

        for input_string, expected_floor_output in zip(input_strings, expected_sqr_ft_of_paper):
            self.__class__.day2.reset()

            self.assertEqual(expected_initial_sqr_ft_of_paper, self.__class__.day2.get_total_paper_required())

            self.__class__.day2.calc_dimensions(input_string)

            actual_sqr_ft_of_paper = self.__class__.day2.get_total_paper_required()

            self.assertEqual(expected_floor_output, actual_sqr_ft_of_paper)

    def test_given_inputs_part2(self):
        self.__class__.day2 = day2.Day2()

        input_strings = [")", "()())", "("]

        expected_basement_iteration_not_found = 0

        expected_basement_outputs = [1, 5, expected_basement_iteration_not_found]

        for input_string, expected_basement_output in zip(input_strings, expected_basement_outputs):
            self.__class__.day2.reset()

            self.assertEqual(expected_basement_iteration_not_found, self.__class__.day2.get_basement_interation())

            self.__class__.day2.calc_dimensions(input_string)

            actual_basement_value = self.__class__.day2.get_basement_interation()

            self.assertEqual(expected_basement_output, actual_basement_value)

    def test_bad_inputs(self):
        self.__class__.day2 = day2.Day2()

        expected_bad_data_exception = "Invalid data type given"
        expected_bad_string_composition_exception = "Invalid string composition given"

        try:
            self.__class__.day2.calc_dimensions(1)
            self.assertTrue(False, "Exception not thrown")
        except day2.AoC2015Day2Exception as excep:
            self.assertTrue(expected_bad_data_exception in str(excep))

        try:
            self.__class__.day2.calc_dimensions("Lobster Thermidor and Spam")
            self.assertTrue(False, "Exception not thrown")
        except day2.AoC2015Day2Exception as excep:
            self.assertTrue(expected_bad_string_composition_exception in str(excep))
