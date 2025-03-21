// GroveEngine 2
// Copyright (C) 2020-2025 usernameak
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License, version 3, as
// published by the Free Software Foundation.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <gtlUtil/CommandLineParser.h>
#include <testutils.h>

int CommandLineParserTest(int argc, char **const argv) {
    gtlUtil::CommandLineParser parser;
    auto &testArg  = parser.registerArgument(GTXT("-test"));
    auto &test1Arg = parser.registerArgument(GTXT("-test1"));
    auto &test2Arg = parser.registerRepeatableArgument(GTXT("-test2"));
    auto &test3Arg = parser.registerValueArgument(GTXT("-test3"));
    auto &test4Arg = parser.registerRepeatableArgument(GTXT("-test4"));
    auto &test5Arg = parser.registerValueArgument(GTXT("-test5"));

    const gtl::WIDECHAR *testArgs[] = {
        GTXT("app"),
        GTXT("-test"),
        GTXT("-test2"),
        GTXT("value"),
        GTXT("-test2"),
        GTXT("value2"),
        GTXT("-test5"),
        GTXT("value3"),
        nullptr
    };

    parser.parse(std::size(testArgs) - 1, testArgs);

    testCheck(testArg);
    testCheck(!test1Arg);

    testCheck(test2Arg);
    testCheck(test2Arg.size() == 2);
    testCheck(test2Arg[0] == GTXT("value"));
    testCheck(test2Arg[1] == GTXT("value2"));

    testCheck(!test3Arg);

    testCheck(!test4Arg);

    testCheck(test5Arg);
    testCheck(*test5Arg == GTXT("value3"));

    return 0;
}
