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

#include "testutils.h"
#include "testMockResMgr.h"
#include "gtlModule/ModuleLoader.h"

#include <grUi/Style/GSS/Parser.h>
#include <grUi/Style/GSS/Tokenizer.h>
#include <grUi/Style/GSS/StyleSheet.h>
#include <grUi/GUI_Module.h>
#include <grUi/Widget/Window/Frame.h>

int GSSTest(int argc, char **const argv) {
    gnaSingleton<gtlModuleLoader>()->loadModule(&GROVE2_MODULE_INFO(grUi));

    nxf_setRM(new testMockResourceManager);

    grUiGSSParser parser;

    grUiGSSTokenizer tokenizer(parser);
    tokenizer.setChars(R"(
        grUiFrame {
            background-image: -gr-9patch(url(resource://root/textures/ui/frame.9.png));
            color: #FF00FF;
        }

        .a.b {
            background-image: url(resource://root/textures/test.png);
            color: maroon;
        }

        .a.c {
            background-image: url(resource://root/textures/test3.png);
            color: rgba(0.5, 0.0, 1.0, 0.8);
        }

        .c .a {
            background-image: url(resource://root/textures/test4.png);
            color: rgb(64, 23, 25);
        }

        .b .a {
            -gr-icon: -gr-sprite(url(resource://root/textures/test2.png));
            color: rgb(20%, 30%, 40%);
        }
    )");

    testCheckStatus(tokenizer.tokenize());

    std::vector<grUiGSSRule> ruleList;
    testCheckStatus(parser.parse(ruleList));

    grUiGSSStyleSheet styleSheet;
    for (auto &rule : ruleList) {
        styleSheet.addRule(std::move(rule));
    }

    auto layout = gnaNew<grUiWidgetLayout>();
    layout->add_styleClass("b");

    auto frame = gnaNew<grUiFrame>();
    frame->add_styleClass("a");
    frame->add_styleClass("c");

    layout->add(frame);

    grUiGSSStyleSheet::FinalRuleList finalRuleList;
    styleSheet.matchRulesAgainstWidget(frame, finalRuleList);

    std::vector<uint32_t> requiredIndexes{ 0, 2, 4 };
    std::vector<uint32_t> indexes;
    for (const auto &rule : finalRuleList) {
        indexes.push_back(rule.get().index);
    }
    testCheck(indexes == requiredIndexes);

    // grUi::staticRelease();
    // TODO: release module

    nxf_setRM(nullptr);

    return 0;
}
