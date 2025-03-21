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

#include <grUi/UiDLL.h>
#include <gtlString/PooledString.h>
#include <gtlUtil/Hash.h>
#include <vector>

namespace grUiGSSSelectors {
    struct Specificity {
        uint8_t idSpecificity;
        uint8_t classSpecificity;
        uint8_t elementSpecificity;

        bool operator<(Specificity other) const {
            return std::tie(idSpecificity, classSpecificity, elementSpecificity) <
                   std::tie(other.idSpecificity, other.classSpecificity, other.elementSpecificity);
        }

        bool operator>(Specificity other) const {
            return std::tie(idSpecificity, classSpecificity, elementSpecificity) >
                   std::tie(other.idSpecificity, other.classSpecificity, other.elementSpecificity);
        }

        bool operator==(Specificity other) const {
            return std::tie(idSpecificity, classSpecificity, elementSpecificity) ==
                   std::tie(other.idSpecificity, other.classSpecificity, other.elementSpecificity);
        }

        bool operator!=(Specificity other) const {
            return !operator==(other);
        }

        Specificity &operator+=(Specificity other) {
            idSpecificity += other.idSpecificity;
            classSpecificity += other.classSpecificity;
            elementSpecificity += other.elementSpecificity;

            return *this;
        }

        Specificity operator+(Specificity other) const {
            Specificity result = *this;
            result += other;
            return result;
        }
    };

    struct Selector {
        enum Type {
            TYPE_ID,
            TYPE_CLASS,
            TYPE_ELEMENT,
            TYPE_PSEUDOCLASS,
            TYPE_ANY
        } type = TYPE_ID;

        gtl::PooledAString name;

        bool operator==(const Selector &o) const {
            return o.type == type && o.name == name;
        }

        bool operator!=(const Selector &o) const {
            return !operator==(o);
        }

        Specificity computeSpecificity() const {
            if (type == TYPE_ID) {
                return { 1, 0, 0 };
            } else if (type == TYPE_CLASS) {
                return { 0, 1, 0 };
            } else if (type == TYPE_ELEMENT) {
                return { 0, 0, 1 };
            } else {
                return { 0, 0, 0 };
            }
        }
    };

    struct CompoundSelector {
        enum Combinator {
            COMBINATOR_NONE,
            COMBINATOR_DESCENDANT,
            COMBINATOR_CHILD,
        } combinator = COMBINATOR_NONE;

        std::vector<Selector> selectors;

        Specificity computeSpecificity() const {
            Specificity spec{};
            for (auto &sel : selectors) {
                spec += sel.computeSpecificity();
            }
            return spec;
        }
    };

    struct ComplexSelector {
        std::vector<CompoundSelector> compoundSelectors;

        bool cleanupExtraneousSelectors() {
            while (!compoundSelectors.empty() && compoundSelectors.back().selectors.empty()) {
                compoundSelectors.pop_back();
            }
            auto &csel = compoundSelectors.back();
            if (csel.combinator != CompoundSelector::COMBINATOR_DESCENDANT &&
                csel.combinator != CompoundSelector::COMBINATOR_NONE) {
                return false;
            }
            csel.combinator = CompoundSelector::COMBINATOR_NONE;
            return true;
        }

        bool empty() const {
            return compoundSelectors.empty();
        }

        Specificity computeSpecificity() const {
            Specificity spec{};
            for (auto &csel : compoundSelectors) {
                spec += csel.computeSpecificity();
            }
            return spec;
        }
    };
}

namespace std {
    template <>
    struct hash<grUiGSSSelectors::Selector> {
        std::size_t operator()(grUiGSSSelectors::Selector const &s) const noexcept {
            std::size_t seed = 0;
            gutlHashCombine(seed, s.type);
            gutlHashCombine(seed, s.name);

            return seed;
        }
    };
}
