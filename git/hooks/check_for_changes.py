#!/bin/python
# Python script to check for changes in the current git repo

import os
import enum
from git import Repo

DEBUG = True


class ModuleEnum(enum.Enum):
    AoC2015 = "2015"


def check_for_changes():
    dir_2015 = "2015"
    exclude_dirs = ["test"]

    ret_dict = {}
    repo = Repo(os.getcwd())

    changes_in_2015 = False

    if DEBUG:
        print(repo.index.diff(repo.head.commit))
    for diff_object in repo.index.diff(repo.head.commit):
        if DEBUG:
            print(diff_object.a_path)
        if all(ex_dir not in diff_object.a_path for ex_dir in exclude_dirs):
            if dir_2015 in diff_object.a_path:
                changes_in_2015 = True

    ret_dict.update({ModuleEnum.AoC2015.name: changes_in_2015})

    return ret_dict


if __name__ == "__main__":
    print(check_for_changes())
