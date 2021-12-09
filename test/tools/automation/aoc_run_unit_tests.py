#!/bin/python
# Python script to build the project

import argparse
import enum
import os
import subprocess
import yaml

DEFAULT_CONFIG_FILE = "../script_configs/aoc_run_2015_unit_tests.yaml"
EXE_PATH_KAY = "exePath"
TEST_TYPE_KEY = "testType"
UNIT_KEY = "unit"
GET_TESTS_KEY = "getTests"

PASS_STRING = "PASS"
FAIL_STRING = "FAIL"
VERSION_STRING = "Version:"
SPLIT_CHAR = ":"

TEST_NAME_POSITION = 3
RESULT_POSITION = 4

AOC_EXCEPTION_INVALID_INPUT_FILE = "Input file does not exist"
AOC_EXCEPTION_MISSING_INPUT_PARAM = "Required input value not found: "


class AoCRunUnitTestsExitCodeEnum(enum.Enum):
    Success = 0
    BadInputFile = 1
    RunError = 2
    ParseOutputError = 3
    FailedTestError = 4


class AoCRunUnitTestException(Exception):

    def __init__(self, value):
        self.value = value

    def __str__(self):
        return repr(self.value)


class AoCRunUnitTests:

    def __init__(self, exe_path, test_type, unit_key, get_tests):
        self.exe_path = exe_path
        self.test_type = test_type
        self.unit_key = unit_key
        self.get_tests = get_tests
        self._passes = 0
        self._fails = 0
        self._DEBUG = True

    def __build_exe_cmd(self):
        return ''.join([os.path.join(os.getcwd(), self.exe_path), " --testType ", self.test_type, " --unit ",
                        self.unit_key, " --getTests ", self.get_tests])

    def __exe_dir(self):
        return os.path.dirname(os.path.join(os.getcwd(), self.exe_path))

    @staticmethod
    def __parse_output(pass_dict, fail_dict):
        ret_val = AoCRunUnitTestsExitCodeEnum.FailedTestError.value

        if fail_dict:
            for value in fail_dict:
                print(value)
        elif pass_dict:
            ret_val = AoCRunUnitTestsExitCodeEnum.Success.value

        return ret_val

    def __run_exe(self, exe_command):
        current_dir = os.getcwd()

        os.chdir(self.__exe_dir())

        pass_dict = {}
        fail_dict = {}

        try:
            process = subprocess.Popen(exe_command, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                                       universal_newlines=True, shell=True)

            for line in process.stdout.readlines():
                if self._DEBUG:
                    print(line)

                if VERSION_STRING in line:
                    # TODO capture version number
                    continue

                if SPLIT_CHAR not in line or VERSION_STRING in line:
                    continue

                result = line.split(SPLIT_CHAR)

                if PASS_STRING in result[RESULT_POSITION]:
                    pass_dict.update({result[TEST_NAME_POSITION]: True})
                else:
                    fail_dict.update({result[TEST_NAME_POSITION]: False})

            for line in process.stderr.readlines():
                print(line)

        except Exception as e:
            print(str(e))

        os.chdir(current_dir)

        return pass_dict, fail_dict

    def set_debug_prints(self, debug):
        self._DEBUG = debug

    def run_test_exe(self):

        exe_command = self.__build_exe_cmd()

        if self._DEBUG:
            print(exe_command)

        pass_dict, fail_dict = self.__run_exe(exe_command)

        return self.__parse_output(pass_dict, fail_dict)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Build Library and Exes.')
    parser.add_argument('--configFile', nargs="+", dest='config_file_path', type=str,
                        help='sum the integers (default: find the max)')

    args = parser.parse_args()

    if not args.config_file_path:
        config_file_path = DEFAULT_CONFIG_FILE
    else:
        config_file_path = args.config_file_path[0]

    if not os.path.exists(config_file_path):
        raise AoCRunUnitTestException(AOC_EXCEPTION_INVALID_INPUT_FILE)

    with open(config_file_path) as config_file:
        input_data = yaml.safe_load(config_file)

        if EXE_PATH_KAY in input_data:
            input_exe_path = input_data[EXE_PATH_KAY]
        else:
            raise AoCRunUnitTestException(''.join([AOC_EXCEPTION_MISSING_INPUT_PARAM, TEST_TYPE_KEY]))

        if TEST_TYPE_KEY in input_data:
            input_test_type = input_data[TEST_TYPE_KEY]
        else:
            raise AoCRunUnitTestException(''.join([AOC_EXCEPTION_MISSING_INPUT_PARAM, TEST_TYPE_KEY]))

        if UNIT_KEY in input_data:
            input_unit_key = input_data[UNIT_KEY]
        else:
            raise AoCRunUnitTestException(''.join([AOC_EXCEPTION_MISSING_INPUT_PARAM, UNIT_KEY]))

        if GET_TESTS_KEY in input_data:
            input_get_tests = input_data[GET_TESTS_KEY]
        else:
            raise AoCRunUnitTestException(''.join([AOC_EXCEPTION_MISSING_INPUT_PARAM, GET_TESTS_KEY]))

        aoc_run_unit_tests = AoCRunUnitTests(input_exe_path, input_test_type, input_unit_key, input_get_tests)

        exit(aoc_run_unit_tests.run_test_exe())

    exit(AoCRunUnitTestsExitCodeEnum.BadInputFile.value)
