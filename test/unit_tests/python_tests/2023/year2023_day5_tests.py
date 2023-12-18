import importlib
import unittest


class AoC2023Day5Test(unittest.TestCase):
    day = None

    @classmethod
    def setUpClass(cls):
        try:
            spec = importlib.util.spec_from_file_location(
                "mod", "../../../../python/2023/year2023_day5.py"
            )
            cls.day = importlib.util.module_from_spec(spec)
            spec.loader.exec_module(cls.day)
        except FileNotFoundError as e:
            print(e)
            print("Failed importing AoC 2023 day")
            exit(-1)

    def setUp(self):
        self.day5_instance = self.__class__.day.Day5()

    def tearDown(self):
        self.day5_instance.reset()

    def test_given_inputs_lowest_seed_location(self):
        input_strings = [
            "seeds: 79 14 55 13\n",
            "\n",
            "seed-to-soil map:\n",
            "50 98 2\n",
            "52 50 48\n",
            "\n",
            "soil-to-fertilizer map:\n",
            "0 15 37\n",
            "37 52 2\n",
            "39 0 15\n",
            "\n",
            "fertilizer-to-water map:\n",
            "49 53 8\n",
            "0 11 42\n",
            "42 0 7\n",
            "57 7 4\n",
            "\n",
            "water-to-light map:\n" "88 18 7\n",
            "18 25 70\n",
            "\n",
            "light-to-temperature map:\n",
            "45 77 23\n",
            "81 45 19\n",
            "68 64 13\n",
            "\n",
            "temperature-to-humidity map:\n",
            "0 69 1\n",
            "1 0 69\n",
            "\n",
            "humidity-to-location map:\n",
            "60 56 37\n",
            "56 93 4\n",
        ]
        expected_lowest_location = 35
        expected_init_lowest_location = -1

        self.assertEqual(
            expected_init_lowest_location,
            self.day5_instance.get_lowest_location(),
        )
        self.day5_instance.parse_almanac(input_strings)
        self.day5_instance.search_for_seed_location()
        self.assertEqual(
            expected_lowest_location,
            self.day5_instance.get_lowest_location(),
        )
        self.day5_instance.reset()
        self.assertEqual(
            expected_init_lowest_location,
            self.day5_instance.get_lowest_location(),
        )

    def test_given_inputs_lowest_seed_range_location(self):
        input_strings = [
            "seeds: 79 14 55 13\n",
            "\n",
            "seed-to-soil map:\n",
            "50 98 2\n",
            "52 50 48\n",
            "\n",
            "soil-to-fertilizer map:\n",
            "0 15 37\n",
            "37 52 2\n",
            "39 0 15\n",
            "\n",
            "fertilizer-to-water map:\n",
            "49 53 8\n",
            "0 11 42\n",
            "42 0 7\n",
            "57 7 4\n",
            "\n",
            "water-to-light map:\n" "88 18 7\n",
            "18 25 70\n",
            "\n",
            "light-to-temperature map:\n",
            "45 77 23\n",
            "81 45 19\n",
            "68 64 13\n",
            "\n",
            "temperature-to-humidity map:\n",
            "0 69 1\n",
            "1 0 69\n",
            "\n",
            "humidity-to-location map:\n",
            "60 56 37\n",
            "56 93 4\n",
        ]
        expected_lowest_location = 46
        expected_init_lowest_location = -1

        self.assertEqual(
            expected_init_lowest_location,
            self.day5_instance.get_lowest_location(),
        )
        self.day5_instance.parse_almanac(input_strings)
        self.day5_instance.search_for_seed_location_seed_range()
        self.assertEqual(
            expected_lowest_location,
            self.day5_instance.get_lowest_location(),
        )
        self.day5_instance.reset()
        self.assertEqual(
            expected_init_lowest_location,
            self.day5_instance.get_lowest_location(),
        )

    def test_bad_inputs(self):
        expected_bad_data_exception = "Invalid data type given"
        try:
            self.day5_instance.search_schematic(1)
            self.assertTrue(False, "Exception not thrown")
        except self.day.AoC2023Day3Exception as excep:
            self.assertTrue(expected_bad_data_exception in str(excep))
