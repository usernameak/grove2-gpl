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

#include "StyleManager.h"

#include "GSS/StyleSheet.h"
#include "GSS/Parser.h"
#include <nxfResource/ResourceManager.h>

grUiStyleManager::grUiStyleManager() = default;
grUiStyleManager::~grUiStyleManager() = default;

gnaPointer<grUiGSSStyleSheet> grUiStyleManager::findStyleSheet(gtl::PooledAString name) {
    // check the cache
    auto it = m_cachedStyleSheets.find(name);
    if (it != m_cachedStyleSheets.end()) {
        return it->second;
    }

    auto &ss = m_cachedStyleSheets[name];

    ss = gnaNew<grUiGSSStyleSheet>();

    gtl::String filename = gtl::String::format(GTXT("/ui/styles/%hs.gss"), name.toCString());

    // get a stream
    gnaPointer<nxfInputStream> stream;
    gnaStatus status = nxf_getRM()->get_resourceStream(filename, stream);
    if (!status) {
        GR_WARNING(GTXT("Stylesheet %ls not found (%ls), falling back to empty stylesheet"),
            filename.toCString(),
            status.get_errorMessage().toCString());
        return ss;
    }

    grUiGSSParser parser;
    grUiGSSTokenizer tokenizer(parser);

    // read the characters from file
    gtl::AString chars;
    status = stream->readAllAsString(chars);
    if (!status) {
        GR_WARNING(GTXT("Stylesheet %ls could not be read (%ls), falling back to empty stylesheet"),
            filename.toCString(),
            status.get_errorMessage().toCString());
        return ss;
    }

    // tokenize the characters
    tokenizer.setChars(chars);
    status = tokenizer.tokenize();
    if (!status) {
        GR_WARNING(GTXT("Stylesheet %ls could not be tokenized (%ls), falling back to empty stylesheet"),
            filename.toCString(),
            status.get_errorMessage().toCString());
        return ss;
    }

    // parse the stream of tokens now
    std::vector<grUiGSSRule> ruleList;
    status = parser.parse(ruleList);
    if (!status) {
        GR_WARNING(GTXT("Stylesheet %ls could not be parsed (%ls), falling back to empty stylesheet"),
            filename.toCString(),
            status.get_errorMessage().toCString());
        return ss;
    }

    // build an optimized stylesheet out of the rule list
    for (auto &rule : ruleList) {
        ss->addRule(std::move(rule));
    }

    return ss;
}

void grUiStyleManager::dropCaches() {
    m_cachedStyleSheets.clear();
}

GNA_SINGLETON_IMPLEMENT(grUiStyleManager);
