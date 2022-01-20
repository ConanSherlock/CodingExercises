#!/bin/python
# Python script to build the project

import argparse
import enum
import os
import shutil
import yaml

DEFAULT_CONFIG_FILE = "../script_configs/aoc_build_all.yaml"
BUILD_DIR_KEY = "buildDir"
BUILD_TYPE_KEY = "buildType"
TARGET_KEY = "target"

MIN_GW = "mingw32-make.exe"

BUILD_FILES = ["cmake_install.cmake", "CMakeCache.txt", "compile_commands.json", "Makefile"]
BUILD_DIRS = ["CMakeFiles"]

AOC_EXCEPTION_INVALID_INPUT_FILE = "Input file does not exist"
AOC_EXCEPTION_MISSING_INPUT_PARAM = "Required input value not found: "


class AoCBuildExitCodeEnum(enum.Enum):
    Success = 0
    BadInputFile = 1
    CleanError = 2
    CMakeError = 3
    MakeError = 4


class AoCBuildException(Exception):

    def __init__(self, value):
        self.value = value

    def __str__(self):
        return repr(self.value)


class AoCBuild:

    def __init__(self, build_dir):
        self.build_dir = build_dir
        self.build_type = "Release"
        self.target = "all"
        self.DEBUG = False

    def __clean_build_files(self):
        try:
            if os.path.exists(self.build_dir):
                shutil.rmtree(self.build_dir)
        except OSError as e:
            raise e

    def __generate_cmake(self):
        cmake_command = "cmake ../../../CMakeLists.txt -G \"MinGW Makefiles\" -B %s -DCMAKE_BUILD_TYPE=%s " \
                        "-DCMAKE_EXPORT_COMPILE_COMMANDS=ON" % (self.build_dir, self.build_type)

        if self.DEBUG:
            print(cmake_command)

        return os.system(cmake_command)

    def __make(self):
        make_command = "%s %s" % (MIN_GW, self.target)

        current_dir = os.getcwd()

        if self.DEBUG:
            print(make_command)

        os.chdir(self.build_dir)

        try:
            ret_val = os.system(make_command)
        except Exception as e:
            print(str(e))
            ret_val = AoCBuildExitCodeEnum.MakeError.value

        os.chdir(current_dir)

        return ret_val

    def set_build_dir(self, build_dir):
        self.build_dir = build_dir

    def set_build_type(self, build_type):
        self.build_type = build_type

    def set_target(self, target):
        self.target = target

    def set_debug_prints(self, debug):
        self.DEBUG = debug

    def build_aoc_code(self):
        try:
            self.__clean_build_files()
        except OSError:
            return AoCBuildExitCodeEnum.CleanError.value

        if self.__generate_cmake() != AoCBuildExitCodeEnum.Success.value:
            return AoCBuildExitCodeEnum.CMakeError.value

        if self.__make() != AoCBuildExitCodeEnum.Success.value:
            return AoCBuildExitCodeEnum.CMakeError.value

        return AoCBuildExitCodeEnum.Success.value


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
        raise AoCBuildException(AOC_EXCEPTION_INVALID_INPUT_FILE)

    with open(config_file_path) as config_file:
        input_data = yaml.safe_load(config_file)

        if BUILD_DIR_KEY in input_data:
            input_build_dir = input_data[BUILD_DIR_KEY]
        else:
            raise AoCBuildException(''.join([AOC_EXCEPTION_MISSING_INPUT_PARAM, BUILD_DIR_KEY]))

        if BUILD_TYPE_KEY in input_data:
            input_build_type = input_data[BUILD_TYPE_KEY]
        else:
            raise AoCBuildException(''.join([AOC_EXCEPTION_MISSING_INPUT_PARAM, BUILD_DIR_KEY]))

        if TARGET_KEY in input_data:
            input_target = input_data[TARGET_KEY]
        else:
            raise AoCBuildException(''.join([AOC_EXCEPTION_MISSING_INPUT_PARAM, TARGET_KEY]))

        aoc_build = AoCBuild(input_build_dir)
        aoc_build.set_build_type(input_build_type)
        aoc_build.set_target(input_target)

        exit(aoc_build.build_aoc_code())

    exit(AoCBuildExitCodeEnum.BadInputFile.value)
