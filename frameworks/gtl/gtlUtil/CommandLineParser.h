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

#pragma once

#include <gtlString/CString.h>
#include <gtlString/String.h>

namespace gtlUtil {
    class GTL_DLLIMPEXP CommandLineParser {
    public:
        class ArgumentInfo {
            friend class CommandLineParser;

            gtl::String name;
            bool requiresValue : 1;
            bool isRepeatable  : 1;

            bool hasValue  : 1;

            std::vector<gtl::String> values;

        public:
            explicit ArgumentInfo(const gtl::String &argumentName) : requiresValue(false),
                                                                     isRepeatable(false),
                                                                     hasValue(false) {}

            explicit operator bool() const {
                return hasValue;
            }

            [[nodiscard]] size_t size() const {
                return values.size();
            }

            const gtl::String &operator*() const {
                assert(requiresValue && hasValue && !isRepeatable);

                return values.front();
            }

            const gtl::String *operator->() const {
                return &operator*();
            }

            const gtl::String &operator[](std::size_t index) const {
                assert(requiresValue && hasValue && isRepeatable);

                return values.at(index);
            }
        };

    private:
        std::unordered_map<gtl::String, ArgumentInfo> m_arguments;

    public:
        ArgumentInfo &registerArgument(const gtl::WIDECHAR *argumentName) {
            return m_arguments
                .emplace(std::piecewise_construct,
                    std::forward_as_tuple(argumentName),
                    std::forward_as_tuple(argumentName))
                .first->second;
        }

        ArgumentInfo &registerValueArgument(const gtl::WIDECHAR *argumentName) {
            ArgumentInfo &info = registerArgument(argumentName);
            info.requiresValue = true;
            return info;
        }

        ArgumentInfo &registerRepeatableArgument(const gtl::WIDECHAR *argumentName) {
            ArgumentInfo &info = registerArgument(argumentName);
            info.requiresValue = true;
            info.isRepeatable  = true;
            return info;
        }

        void parse(int argc, const gtl::WIDECHAR **argv);

        void parse(int argc, gtl::WIDECHAR **argv) {
            parse(argc, const_cast<const gtl::WIDECHAR **>(argv));
        }
    };
}
