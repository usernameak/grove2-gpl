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

#include "CommandLineParser.h"

#include "Logging.h"

void gtlUtil::CommandLineParser::parse(int argc, const gtl::WIDECHAR **argv) {
    for (int i = 1; i < argc; i++) {
        const gtl::WIDECHAR *arg = argv[i];
        auto it = m_arguments.find(arg);
        if (it == m_arguments.end()) {
            GR_FATAL(GTXT("Unknown command-line argument %ls"), arg);
        }

        auto &info = it->second;
        if (!info.requiresValue && info.hasValue) {
            GR_FATAL(GTXT("Command-line argument %ls specified multiple times"), arg);
        }
        info.hasValue = true;
        if (info.requiresValue) {
            if (++i >= argc) {
                GR_FATAL(GTXT("No value specified for command-line argument %ls"), arg);
            }

            if (!info.isRepeatable && !info.values.empty()) {
                GR_FATAL(GTXT("Command-line argument %ls specified multiple times"), arg);
            }

            info.values.emplace_back(argv[i]);
        }
    }
}
