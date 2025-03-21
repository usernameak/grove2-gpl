#!/bin/zsh
find . \( -path './thirdparty' -o -path './ged/thirdparty' -o -path './grRender/thirdparty' -o -path './out' \) -prune -o -type f \( -name '*.cpp' -o -name '*.h' -o -name '*.c' \) -exec clang-format -style=file -i {} +
