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

#include "gtlModule/ServiceDiscoverer.h"


#include <grApplication.h>

#include <gtlUtil/Logging.h>

#include <gtlString/CString.h>
#include <nxfIO/FsPlatform.h>
#include <nxfResource/ResourceManager.h>
#include <nxfResource/FlatFileResourceManager.h>

#include <grRenderCore/RenderInterface.h>

#include <gtlModule/ModuleLoader.h>
#include <grUiNative/Manager/UiManager.h>
#include <grUi/Widget/Window/RootWindowManager.h>

#include <nxfResource/RMEx/ExtendedResourceManager.h>

#if defined(_DEBUG) && defined(_MSC_VER)
#include <crtdbg.h>
#endif

grApplication *gr_gApplication;

grApplication::grApplication() : m_engine(grEngine::Engine::createEngine(this)) {
    grEngine::gEngine = m_engine;
}

void grApplication::gameLoop() {
    m_engine->runEventLoop();
}

void grApplication::preAppStartup(int argc, gtl::WIDECHAR **wargv) {
    gnaSingleton<gtlModuleLoader>()->loadModule(get_moduleInfo());

    m_engine->engineInit();
}

void grApplication::tick(float deltaTimeF) {
    grUi_gRootWindowManager->tick(deltaTimeF);
    grUi_gRootWindowManager->update();

    grRenderCore::g_renderInterface->m_renderStats.onFrameStart();
    grUi_gRootWindowManager->nativeWidgetPreDraw(deltaTimeF);
    grUi_gRootWindowManager->nativeWidgetDraw();
    grUi_gRootWindowManager->nativeWidgetPresent();
}

void grApplication::exitApplication() {
    grEngine::gEngine->shutdown();
}

void grApplication::initVideo() {
    grRenderCore::g_renderInterface =
        (grRenderCore::RenderInterface *)gnaSingleton<gtlServiceDiscoverer>()->lookupService("RenderInterface");

    if (!grRenderCore::g_renderInterface)
        GR_FATAL(GTXT("Cound not look up the render interface"));

    grRenderCore::g_renderInterface->initialize();
}

static void grPostStartup() {
    gr_gUiManager = gtlNew grUiManager;
    gr_gUiManager->init();

    gr_gApplication->appStartup();
}

static void grShutdown() {
    gr_gUiManager->deinit();
    gtlDelete gr_gUiManager;
    gr_gUiManager = nullptr;
}

static int grStartup(int argc, gtl::WIDECHAR **wargv) {
    gr_gApplication = grApplication::create();

    gtl::String userdataDirectory = GTXT(".");
    gtl::String resourcesDir      = grFsPlatform::combinePaths(userdataDirectory, GTXT("enginedata"));

    for (int i = 1; i < argc; i++) {
        gtl::WIDECHAR *arg = wargv[i];
        if (gtl::StrCmp(GTXT("+enginedata"), arg) == 0) {
            if (++i >= argc)
                GR_FATAL(GTXT("no argument for +enginedata"));
            resourcesDir = wargv[i];
        } else if (arg[0] == GTXT('+')) {
            if (++i >= argc)
                GR_FATAL(GTXT("no argument for %ls"), arg);
        } else {
            GR_FATAL(GTXT("unknown argument %ls"), wargv[i]);
        }
    }
    auto *resMan = gtlNew nxfResource::ExtendedResourceManager;
    resMan->addArchiveToNamespace(nxfResource::ExtendedResourceManager::NS_ENGINE,
        gtlNew nxfFlatFileResourceManager(resourcesDir));
    nxf_setRM(resMan);

    gr_gApplication->preAppStartup(argc, wargv);
    gr_gApplication->initVideo();
    grPostStartup();
    gr_gApplication->gameLoop();

    grShutdown();
    // FIXME: grRenderCore::g_renderInterface->destroy();

    return 0;
}

#ifdef _WIN32

#include <windows.h>

extern "C" int WINAPI wWinMain(HINSTANCE hinst, HINSTANCE hprevinst, PWSTR pCmdLine, int nCmdShow) {
    LPWSTR lpCmdLine = GetCommandLineW();
    int argc;
    wchar_t **wargv = CommandLineToArgvW(lpCmdLine, &argc);
    int returnCode  = grStartup(argc, wargv);
    LocalFree(wargv);

#if defined(_DEBUG) && defined(_MSC_VER)
    _CrtDumpMemoryLeaks();
#endif

    return returnCode;
}
#else
#error "unsupported platform"
#endif
