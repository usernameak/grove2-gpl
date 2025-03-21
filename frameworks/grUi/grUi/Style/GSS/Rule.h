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

#include "Selector.h"
#include "Props/PropVal.h"

struct grUiGSSRuleProperty {
    gtl::PooledAString name;
    gnaPointer<grUiGSSPropVal> value;
};

struct grUiGSSRule {
    std::vector<grUiGSSSelectors::ComplexSelector> selectorList;
    std::vector<grUiGSSRuleProperty> properties;
};

struct grUiGSSOptimizedRule {
    grUiGSSSelectors::Specificity specificity;
    uint32_t index;

    std::vector<grUiGSSRuleProperty> properties;

    bool compareBySpecificity(const grUiGSSOptimizedRule &other) const {
        return std::tie(specificity, index) <
               std::tie(other.specificity, other.index);
    }
};
