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

#include "Scene.h"

#include <nxfSerialization/NXFFileReader.h>
#include <nxfSerialization/NXFFileWriter.h>

GTL_RTTI_DEFINE(grScene::Scene, GTL_RTTI_INHERITS(gtlObject));
NXF_SERIALIZABLE_DEFINE(grScene::Scene, GR_SCENE_DLLIMPEXP);
GTL_DEFINE_OBJECT_CLONE(grScene::Scene);

grScene::Scene::Scene() {
    m_rootNode = gnaNew<Node>();
}

void grScene::Scene::cloneMembers(gnaWeakPointer<gtlCloneable> dest, gtlCloneContext &cctx) const {
    gtlObject::cloneMembers(dest, cctx);

    gnaWeakPointer<Scene> cDest = dest.cast<Scene>();
    cDest->m_rootNode           = m_rootNode->clone(cctx).cast<Node>();
}

template <nxfSerialization::SerializationInterface TSerializationInterface>
gnaStatus grScene::Scene::serializationImpl(TSerializationInterface &proxy) {
    GNA_CHECK_STATUS(gtlObject::serializationImpl(proxy));

    GNA_CHECK_STATUS(proxy.serialize("rootNode", m_rootNode));

    return GNA_E_OK;
}

void grScene::Scene::postDeserialize() {
    gtlObject::postDeserialize();

    rebuildGeomLightList();
}

void grScene::Scene::update(float deltaTime) {
    m_rootNode->update(deltaTime);
}

void grScene::Scene::postUpdate(float deltaTime) {
    m_rootNode->postUpdate(deltaTime);
}

void grScene::Scene::removeObject(gnaPointer<grScene::SceneObject> obj) {
    if (obj == m_rootNode) {
        GR_FATAL(GTXT("Trying to destroy the root scene node, this will crash the engine!"));
    }
    gnaWeakPointer<grScene::Node> parent = obj->m_parent;
    if (gnaWeakPointer<grScene::Geometry> geom = obj.rttiCast2<grScene::Geometry>()) {
        auto it = std::ranges::find_if(m_geometryObjects, [geom](const auto &p) {
            return p == geom;
        });
        assert(it != m_geometryObjects.end());
        m_geometryObjects.erase(it);
    } else if (gnaPointer<grScene::Light> light = obj.rttiCast2<grScene::Light>()) {
        auto it = std::ranges::find_if(m_lightObjects, [light](const auto &p) {
            return p == light;
        });
        assert(it != m_lightObjects.end());
        m_lightObjects.erase(it);
    }

    if (parent) {
        parent->removeChild(obj);
    }
}

GTL_RTTI_DEFINE(grScene::SceneContainer, GTL_RTTI_INHERITS(gtlRcObject));

void grScene::SceneContainer::addScene(gnaPointer<Scene> scene) {
    m_scenes.emplace_back(std::move(scene));
}

void grScene::SceneContainer::update(float deltaTime) {
    for (gnaWeakPointer<Scene> scene : m_scenes) {
        scene->update(deltaTime);
    }
}

void grScene::SceneContainer::postUpdate(float deltaTime) {
    for (gnaWeakPointer<Scene> scene : m_scenes) {
        scene->postUpdate(deltaTime);
    }
}

void grScene::Scene::postClone() {
    gtlObject::postClone();

    rebuildGeomLightList();
}

void grScene::Scene::rebuildGeomLightList() {
    gnaWeakPointer<grScene::SceneObject> current = m_rootNode;
    while (current) {
        gnaWeakPointer<grScene::Node> node = current.rttiCast2<grScene::Node>();
        if (node && node->firstChild()) {
            current = node->firstChild();
            continue;
        }

        if (gnaWeakPointer<grScene::Geometry> geom = current.rttiCast2<grScene::Geometry>()) {
            m_geometryObjects.push_back(geom);
        } else if (gnaWeakPointer<grScene::Light> light = current.rttiCast2<grScene::Light>()) {
            m_lightObjects.push_back(light);
        }

        while (current) {
            if (current->nextSibling()) {
                current = current->nextSibling();
                break;
            } else {
                current = current->m_parent;
            }
        }
    }
}
