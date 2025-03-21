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

#include "Main.h"


#include "gtlModule/ServiceDiscoverer.h"

#include <ged/UI/Panes/MainPane.h>

#include <nxfResource/FlatFileResourceManager.h>
#include <nxfIO/FsPlatform.h>
#include <gtlString/String.h>

#include <grUi/Widget/Window/RootWindowManager.h>
#include <grUi/Style/StyleManager.h>
#include <grUi/Style/GSS/StyleSheet.h>
#include <grUi/GUI_Module.h>

#include <gtlModule/ModuleInfo.h>

#include "ObjEditor/ObjEditor.h"

#include <grScene/Scene_StaticInit.h>
#include <nxfResource/RMEx/ExtendedResourceManager.h>

static const gtlModuleDependency gedDeps[] = {
    &GROVE2_MODULE_INFO(grUi),
    {}
};

GROVE2_DECLARE_MODULE(ged){
    .moduleName         = "ged",
    .moduleDescription  = GTXT("GroveEngine 2 Editor"),
    .moduleDependencies = gedDeps
};

grApplication *grApplication::create() {
    return gtlNew gedApplication;
}

gtl::String gedApplication::getApplicationName() {
    static gtl::String GED_APP_NAME(GTXT("GEd"));
    return GED_APP_NAME;
}

const gtlModuleInfo *gedApplication::get_moduleInfo() const {
    return &GROVE2_MODULE_INFO(ged);
}

void gedApplication::preAppStartup(int argc, gtl::WIDECHAR **wargv) {
    grApplication::preAppStartup(argc, wargv);

    grScene::staticInit();

    gtl::String editorDir          = GTXT(".");
    gtl::String editorResourcesDir = grFsPlatform::combinePaths(editorDir, GTXT("editordata"));
    gtl::String gameResourcesDir;

    for (int i = 1; i < argc; i++) {
        gtl::WIDECHAR *arg = wargv[i];
        if (gtl::StrCmp(GTXT("+editordata"), arg) == 0) {
            if (++i >= argc)
                GR_FATAL(GTXT("no argument for +editordata"));
            editorResourcesDir = wargv[i];
        } else if (gtl::StrCmp(GTXT("+gamedata"), arg) == 0) {
            if (++i >= argc)
                GR_FATAL(GTXT("no argument for +gamedata"));
            gameResourcesDir = wargv[i];
        }
    }

    auto *rm = dynamic_cast<nxfResource::ExtendedResourceManager *>(nxf_getRM());
    rm->addArchiveToNamespace(nxfResource::ExtendedResourceManager::NS_EDITOR, gtlNew nxfFlatFileResourceManager(editorResourcesDir));

    if (!gameResourcesDir.empty()) {
        rm->clearNamespace(nxfResource::ExtendedResourceManager::NS_GAME);
        auto *arch = gtlNew nxfFlatFileResourceManager(gameResourcesDir);
        rm->addArchiveToNamespace(nxfResource::ExtendedResourceManager::NS_GAME, arch);
        rm->m_editResourceManager = arch;
    }

    gnaSingleton<ged::ObjEditorRegistry>()->registerDefaultEditors();
}

void gedApplication::appStartup() {
    grUi_gRootWindowManager->set_styleSheet(gnaSingleton<grUiStyleManager>()->findStyleSheet("GED"));

    ged_gMainPane = gnaNew<gedMainPane>();
    ged_gMainPane->set_focused(true);
    // grUiWindowLayoutData::center(ged_gMainPane, grUi_gRootWindowManager);
    grUi_gRootWindowManager->add(ged_gMainPane);

    ged_gMainPane->m_projectExplorerPane->refresh();
}
