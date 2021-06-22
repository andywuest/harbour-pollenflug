#/bin/bash
clang-format-9 --sort-includes -i src/**/*.cpp   src/**/*.h   --verbose
clang-format-9 --sort-includes -i tests/**/*.cpp tests/**/*.h --verbose

