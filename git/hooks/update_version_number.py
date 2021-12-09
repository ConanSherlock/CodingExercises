#!/bin/python
# Python script to increment the version number in a version file
import os
from git import Repo


def update_version_number(version_file_path, version_keyword):
    ret_val = False

    try:
        version_file = open(version_file_path, 'r')
        file_lines = version_file.readlines()
        new_file_lines = []

        repo = Repo(os.getcwd())

        for line in file_lines:
            if version_keyword in line:
                new_build_number = int(line.split(version_keyword)[-1].strip("\n").strip("\r"))+1
                line = "%s%s %d\n" % (line.split(version_keyword)[0], version_keyword, new_build_number)
            new_file_lines.append(line)

        version_file.close()

        version_file = open(version_file_path, 'w+')
        version_file.writelines(new_file_lines)
        version_file.close()

        os.system("git add .")

        ret_val = True

    except Exception as e:
        print(e)

    return ret_val


if __name__ == "__main__":
    test_version_file_path = "./inc/private/2015/aoc_2015_version.hpp"
    test_version_keyword = "AOC_2015_BUILD_NUM"

    print(update_version_number(test_version_file_path, test_version_keyword))
