import re
import os
from typing import List


class AoC2023Day4Exception(Exception):
    def __init__(self, value):
        self.value = value
        super().__init__(value)


class Day4:
    INVALID_TYPE_SELECTION = "Invalid data type given"
    NO_GROUPS_FOUND = "No groups found in search data"
    CARD_REGEX = re.compile(r"Card\s+(\d+):\s+((\d+\s+)+)\|\s+((\d+\s+)+)(\d+)")
    CARD_NUMBER_POSITION = 0
    WINNING_NUMBER_POSITION = 1
    PULLED_NUMBERS_POSITION = 3
    FINAL_PULL_NUMBER_POSITION = 5
    SCORE_MULTIPLIER = 2

    def __init__(self):
        self._card_value = 0
        self._sum_card_values = 0
        self._winning_numbers = []
        self._pulled_numbers = []
        self._winning_pulls = 0
        self._winning_card = False
        self._card_copies = {}
        self._total_number_of_scratch_cards = 0

    def reset(self):
        self._card_value = 0
        self._sum_card_values = 0
        self._winning_numbers.clear()
        self._pulled_numbers.clear()
        self._card_copies.clear()
        self._winning_pulls = 0
        self._winning_card = False
        self._total_number_of_scratch_cards = 0

    def calc_scratch_card_value(self, card: str):
        self._winning_card = False

        """Search the schematic for part numbers."""
        if not isinstance(card, str):
            raise AoC2023Day4Exception(f"{self.INVALID_TYPE_SELECTION}: {type(card)}")
        self._winning_pulls = 0
        card_search_match = self.CARD_REGEX.match(card)

        if card_search_match is None:
            raise AoC2023Day4Exception(self.NO_GROUPS_FOUND)
        found_number_groups = card_search_match.groups()

        winning_numbers = self._extract_numbers_as_strings(
            found_number_groups[self.WINNING_NUMBER_POSITION]
        )
        pulled_numbers = self._extract_numbers_as_strings(
            found_number_groups[self.PULLED_NUMBERS_POSITION]
        )
        pulled_numbers.append(found_number_groups[self.FINAL_PULL_NUMBER_POSITION])
        self._winning_numbers = self._convert_str_list_to_int(winning_numbers)
        self._pulled_numbers = self._convert_str_list_to_int(pulled_numbers)
        self._count_winning_pulls()
        self._update_sum_cards_value()

    def calc_total_cards(self, card_list: List[str]):
        self._card_copies = {i: 0 for i in range(len(card_list))}
        for card_num, card in enumerate(card_list):
            self.calc_scratch_card_value(card)
            if self._winning_card:
                self._update_card_copy_dict(card_num)

        for card_num in self._card_copies:
            for i in range(0, self._card_copies[card_num]):
                self.calc_scratch_card_value(card_list[card_num])
                if self._winning_card:
                    self._update_card_copy_dict(card_num)
                else:
                    continue
            self._total_number_of_scratch_cards += self._card_copies[card_num]
        self._total_number_of_scratch_cards += len(card_list)

    def _update_card_copy_dict(self, card_num):
        for i in range(1, self._winning_pulls + 1):
            card_copy_key = card_num + i
            if card_copy_key in self._card_copies:
                self._card_copies[card_copy_key] += 1

    def _count_winning_pulls(self):
        for pulled_number in self._pulled_numbers:
            if pulled_number in self._winning_numbers:
                self._winning_pulls += 1

    def _update_sum_cards_value(self):
        if self._winning_pulls > 0:
            self._card_value = self.SCORE_MULTIPLIER ** (self._winning_pulls - 1)
            self._winning_card = True
        else:
            self._card_value = 0
        self._sum_card_values += self._card_value

    @staticmethod
    def _extract_numbers_as_strings(string_to_parse: str):
        return list(filter(lambda a: a != "", string_to_parse.split(" ")))

    @staticmethod
    def _convert_str_list_to_int(string_list: List[str]):
        return [int(x) for x in string_list]

    def get_total_card_value(self) -> int:
        return self._sum_card_values

    def get_total_cards_won(self) -> int:
        return self._total_number_of_scratch_cards


if __name__ == "__main__":
    day4_file_path = os.path.abspath("../../test/input_data/2023/day4_input.txt")
    if not os.path.exists(day4_file_path):
        raise FileNotFoundError(f"File not found: {day4_file_path}")
    day4 = Day4()
    # try:
    #     with open(day4_file_path, "r") as input_file:
    #         input_scratch_cards = input_file.readlines()
    #         if not input_scratch_cards:
    #             raise AoC2023Day4Exception("Input schematic is empty")
    #         for current_card in input_scratch_cards:
    #             day4.calc_scratch_card_value(current_card)
    # except OSError as e:
    #     raise AoC2023Day4Exception(f"Error reading file: {e}")
    # print("--- Day 4: Scratchcards ---")
    # print(f"Part A Point value of all cards: {day4.get_total_card_value()}")

    day4.reset()
    try:
        with open(day4_file_path, "r") as input_file:
            input_scratch_cards = input_file.readlines()
            if not input_scratch_cards:
                raise AoC2023Day4Exception("Input schematic is empty")
            day4.calc_total_cards(input_scratch_cards)
    except OSError as e:
        raise AoC2023Day4Exception(f"Error reading file: {e}")
    print(f"Part B Sum of all of the gear ratio values: {day4.get_total_cards_won()}")
