#/bin/zsh
find . -regex '.*\.\(cpp\|hpp\|cu\|c\|h\)' -exec clang-format-9 --verbose -i {} \;

