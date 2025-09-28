#!/usr/bin/env python3
#
# As Clangd does not support loading environment variables from the shell, and since
# different systems have libraries at different locations, this intermediate script can
# be used to create a `.clangd` configuration on the fly.
#
# Generate a new `.clangd` configuration with:
# > python3 .clangd-gen.py > .clangd
#
# Author: Mikael Henriksson (2025)
#

import os
import configparser

DIR = os.path.dirname(os.path.realpath(__file__))
CONFIG = configparser.ConfigParser()

def get_include_dir(wrap_file: str, under_dir: str | None = None) -> str:
    """
    Retrieve the include directory from a Meson `wrap_file` that is located under the
    subprojects directory.

    Parameters
    ----------
    wrap_file : `str`
        Path of the Meson wrap file.

    under_dir : `str`
        The under directory of the subproject directory as pointed out by `wrap_file`

    Returns
    -------
    include_dir : `str`
        The directory of the include files
    """
    assert wrap_file[-5:] == ".wrap"
    parser = configparser.ConfigParser()
    subproject_dir: str = ""
    with open(f"{DIR}/subprojects/{wrap_file}") as f:
        parser.read_file(f)
    try:
        subproject_dir = f"{DIR}/subprojects/{parser['wrap-file']['directory']}"
    except:
        subproject_dir = f"{DIR}/subprojects/{wrap_file[:-5]}"
   
    if under_dir is not None:
        return f"{subproject_dir}/{under_dir}"
    else:
        return subproject_dir

compile_flags = [
    "-std=c++23",
    "-Wall",
    "-Wextra",
    "-Wpedantic",
    "-Wno-deprecated",
    f"-I{get_include_dir(wrap_file="abseil-cpp.wrap")}",
    f"-I{get_include_dir(wrap_file="catch2.wrap", under_dir="src")}",
    f"-I{get_include_dir(wrap_file="fmt.wrap", under_dir="include")}",
    f"-I{get_include_dir(wrap_file="json.wrap", under_dir="include")}",
    f"-I{get_include_dir(wrap_file="magic_enum.wrap", under_dir="include")}",
]

# Produce the .clangd configuration
TAB = "    "
print("CompileFlags:\n" + TAB + "Add: [")
for flag in compile_flags:
    print(2 * TAB + flag + ",")
print(TAB + "]")
