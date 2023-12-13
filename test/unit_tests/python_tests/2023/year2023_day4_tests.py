import importlib
import unittest


class AoC2023Day4Test(unittest.TestCase):
    day4 = None

    @classmethod
    def setUpClass(cls):
        try:
            spec = importlib.util.spec_from_file_location(
                "mod", "../../../../python/2023/year2023_day4.py"
            )
            cls.day4 = importlib.util.module_from_spec(spec)
            spec.loader.exec_module(cls.day4)
        except FileNotFoundError as e:
            print(e)
            print("Failed importing AoC 2023 day4")
            exit(-1)

    def setUp(self):
        self.day4_instance = self.__class__.day4.Day4()

    def tearDown(self):
        self.day4_instance.reset()

    def test_given_inputs_total_card_value_and_total_cards(self):
        input_strings = [
            "Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53\n",
            "Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19\n",
            "Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1\n",
            "Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83\n",
            "Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36\n",
            "Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11\n",
        ]

        expected_total_value_of_cards = 13
        expected_total_scratch_cards = 30
        expected_init_total_value_of_cards = 0
        expected_init_total_scratch_cards = 0

        self.assertEqual(
            expected_init_total_value_of_cards,
            self.day4_instance.get_total_cards_value(),
        )
        self.assertEqual(
            expected_init_total_scratch_cards,
            self.day4_instance.get_total_cards_value(),
        )

        for card in input_strings:
            self.day4_instance.calc_scratch_card_value(card)

        self.assertEqual(
            expected_total_value_of_cards, self.day4_instance.get_total_cards_value()
        )

        self.day4_instance.reset()

        self.assertEqual(
            expected_init_total_value_of_cards,
            self.day4_instance.get_total_cards_value(),
        )
        self.assertEqual(
            expected_init_total_scratch_cards,
            self.day4_instance.get_total_cards_after_winnings(),
        )

        self.day4_instance.calc_total_cards(input_strings)
        actual_total_scratch_cards = self.day4_instance.get_total_cards_after_winnings()

        self.assertEqual(expected_total_scratch_cards, actual_total_scratch_cards)

    def test_bad_inputs(self):
        expected_bad_data_exception = "Invalid data type given"
        try:
            self.day4_instance.calc_scratch_card_value(1)
            self.assertTrue(False, "Exception not thrown")
        except self.day4.AoC2023Day4Exception as excep:
            self.assertTrue(expected_bad_data_exception in str(excep))
        try:
            self.day4_instance.calc_total_cards(1)
            self.assertTrue(False, "Exception not thrown")
        except self.day4.AoC2023Day4Exception as excep:
            self.assertTrue(expected_bad_data_exception in str(excep))
