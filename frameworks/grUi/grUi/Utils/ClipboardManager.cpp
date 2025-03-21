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

#include "ClipboardManager.h"

#include <gtlString/String.h>
#include <gtlUtil/Logging.h>

#include <windows.h>

void grUiClipboardManager::set_clipboardString(gtl::String str) {
    if (!OpenClipboard(NULL)) {
        GR_WARNING(GTXT("Failed to open clipboard"));
        return;
    }

    HANDLE hData = GlobalAlloc(GMEM_MOVEABLE, (str.size() + 1) * sizeof(gtl::WIDECHAR));
    if (!hData) {
        GR_WARNING(GTXT("Failed to allocate clipboard data"));
        CloseClipboard();
        return;
    }
    auto data = static_cast<gtl::WIDECHAR *>(GlobalLock(hData));
    if (!data) {
        GR_WARNING(GTXT("Failed to lock clipboard data"));
        CloseClipboard();
        return;
    }
    gtl::StrCpy(data, str.toCString());
    GlobalUnlock(hData);
    if (!SetClipboardData(CF_UNICODETEXT, hData)) {
        GR_WARNING(GTXT("Failed to set clipboard data"));
        CloseClipboard();
        return;
    }
    CloseClipboard();
}

gtl::String grUiClipboardManager::get_clipboardString() {
    if (!OpenClipboard(NULL)) {
        GR_WARNING(GTXT("Failed to open clipboard"));
        return gtl::String();
    }

    HANDLE hData = GetClipboardData(CF_UNICODETEXT);
    if (!hData) {
        GR_WARNING(GTXT("Failed to get clipboard data"));
        CloseClipboard();
        return gtl::String();
    }

    const auto *text = static_cast<const gtl::WIDECHAR *>(GlobalLock(hData));
    if (!text) {
        GR_WARNING(GTXT("Failed to lock clipboard data"));
        CloseClipboard();
        return gtl::String();
    }

    gtl::String ws(text);

    GlobalUnlock(hData);
    CloseClipboard();

    return ws;
}
