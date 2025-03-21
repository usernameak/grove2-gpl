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

#include "gtlLicenseInfo.h"

static const gtl::WIDECHAR *const AUTHOR_NAMES_ENGINE[] = {
    GTXT("\u00A9 2020-2023 Anton \"usernameak\" Korzhuk"),
    GTXT("\u00A9 2022-2023 alexcher"),
    GTXT("\u00A9 2023 NIKEA-SOFT"),
    GTXT("\u00A9 2022 mikhail_fs"),
    nullptr
};

static const gtl::WIDECHAR *const AUTHOR_NAMES_ICU[] = {
    GTXT("\u00A9 1991-2022 Unicode, Inc. All rights reserved."),
    nullptr
};

static const gtl::WIDECHAR *const AUTHOR_NAMES_NLOHMANN_JSON[] = {
    GTXT("\u00A9 2013-2022 Niels Lohmann"),
    nullptr
};

static const gtl::WIDECHAR *const AUTHOR_NAMES_ORDERED_MAP[] = {
    GTXT("\u00A9 2017 Thibaut Goetghebuer-Planchon"),
    nullptr
};

static const gtl::WIDECHAR *const AUTHOR_NAMES_MINIZ[] = {
    GTXT("\u00A9 2013-2014 RAD Game Tools"),
    GTXT("\u00A9 2013-2014 Valve Software"),
    GTXT("\u00A9 2010-2014 Rich Geldreich"),
    GTXT("\u00A9 2010-2014 Tenacious Software LLC"),
    nullptr
};

static const gtl::WIDECHAR *const AUTHOR_NAMES_LZ4[] = {
    GTXT("\u00A9 2011-2020 Yann Collet"),
    nullptr
};

const grUiEngineAboutEntry gtl_gAboutEntries[] = {
    { GTXT("GroveEngine 2"),
        // GTXT("Licensed under the 3-Clause BSD License"),
        nullptr,
        AUTHOR_NAMES_ENGINE },
    { GTXT("ICU4C 71"),
        GTXT("Licensed under the ICU License"),
        AUTHOR_NAMES_ICU },
    { GTXT("nlohmann/json"),
        GTXT("Licensed under the 3-Clause BSD License"),
        AUTHOR_NAMES_NLOHMANN_JSON },
    { GTXT("ordered-map 1.1.0"),
        GTXT("Licensed under the MIT License"),
        AUTHOR_NAMES_ORDERED_MAP },
    { GTXT("miniz 2.2.0"),
        GTXT("Licensed under the MIT License"),
        AUTHOR_NAMES_MINIZ },
    { GTXT("LZ4 Library"),
        GTXT("Licensed under the 2-Clause BSD License"),
        AUTHOR_NAMES_LZ4 },
    { nullptr, nullptr, nullptr }
};
