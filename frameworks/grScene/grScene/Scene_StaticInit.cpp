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

#include "Scene_StaticInit.h"

#include "Scene.h"
#include "SceneEmpty.h"
#include "SceneGeom.h"
#include "SceneNode.h"
#include "Camera.h"
#include "Material/MaterialInstance.h"
#include "SceneObject.h"
#include "Light/SceneLight.h"
#include "nxfSerialization/SerializationTypeRegistry.h"

void grScene::staticInit() {
    using nxfSerialization::SerializationTypeRegistry;

    SceneObject::staticInit();
    MaterialInstance::staticInit();

    auto *registry = gnaSingleton<SerializationTypeRegistry>();
    registry->registerType<Scene>("grScene::Scene");
    registry->registerType<Node>("grScene::Node");
    registry->registerType<Geometry>("grScene::Geometry");
    registry->registerType<Empty>("grScene::Empty");
    registry->registerType<Camera>("grScene::Camera");
    registry->registerType<DirectionalLight>("grScene::DirectionalLight");
    registry->registerType<MaterialInstance>("grScene::MaterialInstance");
}

void grScene::staticRelease() {
    using nxfSerialization::SerializationTypeRegistry;

    auto *registry = gnaSingleton<SerializationTypeRegistry>();
    registry->unregisterType("grScene::Scene");
    registry->unregisterType("grScene::Node");
    registry->unregisterType("grScene::Geometry");
    registry->unregisterType("grScene::Empty");
    registry->unregisterType("grScene::Camera");
    registry->unregisterType("grScene::DirectionalLight");
    registry->unregisterType("grScene::MaterialInstance");

    grScene::MaterialInstance::staticRelease();
    grScene::SceneObject::staticRelease();
}
