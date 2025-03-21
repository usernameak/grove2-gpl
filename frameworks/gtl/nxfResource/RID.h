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

#include <gtlString/String.h>

class nxfResourceManager;

struct nxfRID {
private:
    static inline const gtl::String INVALID_SRID = GTXT("");

public:
    gtl::String name;

    nxfRID() : name(INVALID_SRID) {
    }

    nxfRID(gtl::String name) : name(name) {
    }

    nxfRID &operator=(const nxfRID &other) = default;

    bool operator==(const nxfRID &other) const {
        return name == other.name;
    }

    bool operator!=(const nxfRID &other) const {
        return !(this->operator==(other));
    }

    operator bool() const {
        return name != INVALID_SRID;
    }

    [[nodiscard]] gtl::String toDisplayPathString() const {
        static const gtl::String NONE_STR    = GTXT("<None>");

        if (!operator bool()) {
            return NONE_STR;
        }
        gtl::String str = name;
        return str;
    }
};

namespace std {
    template <>
    struct hash<nxfRID> {
        std::size_t operator()(nxfRID const &s) const noexcept {
            return std::hash<gtl::String>{}(s.name);
        }
    };
}
