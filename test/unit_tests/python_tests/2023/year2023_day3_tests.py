import importlib
import unittest


class AoC2023Day3Test(unittest.TestCase):
    day3 = None

    @classmethod
    def setUpClass(cls):
        try:
            spec = importlib.util.spec_from_file_location(
                "mod", "../../../../python/2023/year2023_day3.py"
            )
            cls.day3 = importlib.util.module_from_spec(spec)
            spec.loader.exec_module(cls.day3)
        except FileNotFoundError as e:
            print(e)
            print("Failed importing AoC 2023 day3")
            exit(-1)

    def setUp(self):
        self.day3_instance = self.__class__.day3.Day3()

    def tearDown(self):
        self.day3_instance.reset()

    def test_given_inputs_sum_part_numbers_sum_gear(self):
        input_strings = [
            "467..114..\n",
            "...*......\n",
            "..35..633.\n",
            "......#...\n",
            "617*......\n",
            ".....+.58.\n",
            "..592.....\n",
            "......755.\n",
            "...$.*....\n",
            ".664.598..\n",
        ]
        expected_found_part_ids_list = [
            467,
            35,
            633,
            617,
            592,
            755,
            664,
            598,
        ]
        expected_sum_parts_ids = 4361
        expected_sum_gears = 467835
        expected_init_found_part_ids = []
        expected_init_expected_sum_parts_ids = 0
        expected_init_expected_sum_gears = 0

        self.assertEqual(
            expected_init_found_part_ids,
            self.day3_instance.get_found_part_ids(),
        )
        self.assertEqual(
            expected_init_expected_sum_parts_ids,
            self.day3_instance.get_sum_part_numbers(),
        )
        self.assertEqual(
            expected_init_expected_sum_gears,
            self.day3_instance.get_sum_gear_ratio(),
        )

        self.day3_instance.search_schematic(input_strings)

        actual_part_ids_list = self.day3_instance.get_found_part_ids()
        self.assertEqual(len(expected_found_part_ids_list), len(actual_part_ids_list))
        for expected_part_ids, actual_part_ids in zip(
            expected_found_part_ids_list, actual_part_ids_list
        ):
            self.assertEqual(expected_part_ids, actual_part_ids)

        self.assertEqual(
            expected_sum_parts_ids, self.day3_instance.get_sum_part_numbers()
        )
        self.assertEqual(
            expected_sum_gears,
            self.day3_instance.get_sum_gear_ratio(),
        )
        print(expected_sum_gears)
        print(self.day3_instance.get_sum_gear_ratio())

        self.day3_instance.reset()

        self.assertEqual(
            expected_init_found_part_ids,
            self.day3_instance.get_found_part_ids(),
        )
        self.assertEqual(
            expected_init_expected_sum_parts_ids,
            self.day3_instance.get_sum_part_numbers(),
        )
        self.assertEqual(
            expected_init_expected_sum_gears,
            self.day3_instance.get_sum_gear_ratio(),
        )

    def test_bad_inputs(self):
        expected_bad_data_exception = "Invalid data type given"
        try:
            self.day3_instance.search_schematic(1)
            self.assertTrue(False, "Exception not thrown")
        except self.day3.AoC2023Day3Exception as excep:
            self.assertTrue(expected_bad_data_exception in str(excep))
