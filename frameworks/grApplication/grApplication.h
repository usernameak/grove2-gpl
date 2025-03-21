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
#include <grEngine/Engine.h>
#include <grEngine/IEngineApplication.h>
#include <gtlModule/ModuleInfo.h>

class grApplication : public grEngine::IEngineApplication {

public:
    grEngine::Engine *m_engine;

    grApplication();
    virtual ~grApplication() = default;

    void gameLoop();

    virtual void appStartup() = 0;
    virtual void preAppStartup(int argc, gtl::WIDECHAR **wargv);
    virtual const gtlModuleInfo *get_moduleInfo() const = 0;

    virtual gtl::String getApplicationName() = 0;

    void initVideo();

    void tick(float deltaTimeF) override;

    void exitApplication();

    static grApplication *create();
};

extern grApplication *gr_gApplication;

#ifdef _WIN32
#ifndef _WIN64
#pragma comment(linker, "/include:_wWinMain@16")
#else
#pragma comment(linker, "/include:wWinMain")
#endif
#endif
