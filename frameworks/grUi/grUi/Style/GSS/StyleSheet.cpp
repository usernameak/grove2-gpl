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

#include "StyleSheet.h"

#include <grUi/Widget/Widget.h>
#include <grUi/Widget/WidgetLayout.h>

GTL_RTTI_DEFINE(grUiGSSStyleSheet, GTL_RTTI_INHERITS(gtlRcObject));

grUiGSSStyleSheet::grUiGSSStyleSheet()
    : m_currentIndex(0) {}

void grUiGSSStyleSheet::addRule(grUiGSSRule &&rule) {
    for (auto &complexSelector : rule.selectorList) {
        RuleTreeNode *currentNode = &m_rootNode;

        assert(!complexSelector.compoundSelectors.empty());
        for (auto it = complexSelector.compoundSelectors.crbegin(); it != complexSelector.compoundSelectors.crend(); ++it) {
            const grUiGSSSelectors::CompoundSelector &csel = *it;

            assert(!csel.selectors.empty());

            grUiGSSSelectors::CompoundSelector::Combinator currentCombinator = csel.combinator;

            for (const grUiGSSSelectors::Selector &sel : csel.selectors) {
                while ((sel.type != currentNode->subnodeType || currentCombinator != currentNode->subnodeCombinator) &&
                       !currentNode->subnodes.empty()) {
                    currentNode = currentNode->createOrGetNext();
                }

                gtl::AString fixedUpName = static_cast<gtl::AString>(sel.name);

                // convert element names to RTTI names (replace __ with ::)
                if (sel.type == grUiGSSSelectors::Selector::TYPE_ELEMENT) {
                    gtl::ASCIICHAR *nameChars = fixedUpName.forceCopy();
                    for (size_t i = 1; i < fixedUpName.size(); i++) {
                        if (nameChars[i - 1] == '_' && nameChars[i] == '_') {
                            nameChars[i - 1] = nameChars[i] = ':';
                        }
                    }
                }

                currentNode->subnodeCombinator = currentCombinator;
                currentNode->subnodeType       = sel.type;
                currentNode                    = &currentNode->subnodes[fixedUpName];
                currentCombinator              = grUiGSSSelectors::CompoundSelector::COMBINATOR_NONE;
            }
        }

        grUiGSSOptimizedRule &optRule = currentNode->rules.emplace_back();
        optRule.specificity           = complexSelector.computeSpecificity();
        optRule.index                 = m_currentIndex++;
        optRule.properties            = rule.properties; // TODO: maybe merge properties from comma-separated selectors?
    }
}

void grUiGSSStyleSheet::matchRulesAgainstWidget(gnaWeakPointer<grUiWidget> widget, FinalRuleList &rules) const {
    matchRulesAgainstWidget(&m_rootNode, widget, rules);

    std::sort(rules.begin(), rules.end(), std::mem_fn(&grUiGSSOptimizedRule::compareBySpecificity));
}

void grUiGSSStyleSheet::matchRulesAgainstWidget(
    const grUiGSSStyleSheet::RuleTreeNode *node,
    gnaWeakPointer<grUiWidget> widget,
    FinalRuleList &rules) const {

    for (; node; node = node->pNext) {
        for (auto &rule : node->rules) {
            rules.push_back(rule);
        }
        gnaWeakPointer<grUiWidget> currentWidget = widget;
        if (node->subnodeCombinator == grUiGSSSelectors::CompoundSelector::COMBINATOR_CHILD ||
            node->subnodeCombinator == grUiGSSSelectors::CompoundSelector::COMBINATOR_DESCENDANT) {
            currentWidget = currentWidget->get_parent();
        }
        while (currentWidget) {
            switch (node->subnodeType) {
            case grUiGSSSelectors::Selector::TYPE_CLASS:
                for (auto &klass : currentWidget->get_styleClasses()) {
                    auto it = node->subnodes.find(klass);
                    if (it == node->subnodes.end()) continue;

                    matchRulesAgainstWidget(&it->second, currentWidget, rules);
                }
                break;
            case grUiGSSSelectors::Selector::TYPE_ID: {
                auto it = node->subnodes.find(currentWidget->get_id());
                if (it == node->subnodes.end()) break;

                matchRulesAgainstWidget(&it->second, currentWidget, rules);
                break;
            }
            case grUiGSSSelectors::Selector::TYPE_ANY:
                for (auto &[name, rule] : node->subnodes) {
                    matchRulesAgainstWidget(&rule, currentWidget, rules);
                }
                break;
            case grUiGSSSelectors::Selector::TYPE_ELEMENT:
                for (const gtlRTTI *rtti = currentWidget->get_rtti(); rtti; rtti = rtti->get_baseClass()) {
                    auto it = node->subnodes.find(rtti->get_className());
                    if (it == node->subnodes.end()) continue;

                    matchRulesAgainstWidget(&it->second, currentWidget, rules);
                }
                break;
            case grUiGSSSelectors::Selector::TYPE_PSEUDOCLASS: {
                static std::unordered_map<gtl::Name, uint64_t> PSEUDOCLASSES = {
                    { "hover", (uint64_t)grUiWidget::STSTBIT_HOVERED },
                    { "active", (uint64_t)grUiWidget::STSTBIT_PRESSED },
                    { "focus", (uint64_t)grUiWidget::STSTBIT_FOCUSED },
                    { "disabled", (uint64_t)grUiWidget::STSTBIT_DISABLED },
                    { "checked", (uint64_t)grUiWidget::STSTBIT_CHECKED },
                    { "-gr-highlight", (uint64_t)grUiWidget::STSTBIT_HIGHLIGHT }
                };
                for (const auto &[name, rule] : node->subnodes) {
                    auto it = PSEUDOCLASSES.find(name);
                    if (it == PSEUDOCLASSES.end()) continue;

                    if (!(currentWidget->get_styleStateBits() & it->second)) continue;

                    matchRulesAgainstWidget(&rule, currentWidget, rules);
                }
                break;
            }
            default:
                if (!node->subnodes.empty()) {
                    GR_WARNING(GTXT("selector type id %d not supported yet"), node->subnodeType);
                }
                break;
            }

            if (node->subnodeCombinator == grUiGSSSelectors::CompoundSelector::COMBINATOR_NONE ||
                node->subnodeCombinator == grUiGSSSelectors::CompoundSelector::COMBINATOR_CHILD) {
                break;
            } else if (node->subnodeCombinator == grUiGSSSelectors::CompoundSelector::COMBINATOR_DESCENDANT) {
                currentWidget = currentWidget->get_parent();
            } else {
                GR_WARNING(GTXT("combinator type id %d not supported yet"), node->subnodeCombinator);
                break;
            }
        }
    }
}
