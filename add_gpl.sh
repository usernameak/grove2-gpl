#!/bin/bash
find -not -path '*thirdparty*' \( -name '*.c' -o -name '*.cpp' -o -name '*.h' -o -name '*.hpp' -o -name '*.java' \) -exec sed -i '0r /d/work/wwmm/legacy_grove2/GPL_NOTICE.txt' {} \;

