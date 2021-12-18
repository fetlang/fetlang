#!/usr/bin/env bash
# Code formatting script

find "../fetishes/" ../src/*.cpp ../src/*.h ../src/tests\
    \( -name '*.h' -o -name '*.cpp' -o -name '*.c' \) -exec clang-format -i {} \;
