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

#include "SceneDLL.h"
#include "SceneNode.h"
#include "SceneGeom.h"
#include "Light/SceneLight.h"

#include <gtlObject/Object.h>

namespace grScene {
    class GR_SCENE_DLLIMPEXP Scene : public gtlObject {
    public:
        GTL_RTTI_DECLARE();
        GTL_DECLARE_OBJECT_CLONE;
        NXF_SERIALIZABLE_DECLARE();

        Scene();

        template <nxfSerialization::SerializationInterface TSerializationInterface>
        gnaStatus serializationImpl(TSerializationInterface &proxy);

        void postDeserialize() override;

        void update(float deltaTime);
        void postUpdate(float deltaTime);

        template <typename T>
        gnaPointer<T> createObject(gnaWeakPointer<grScene::Node> parent = nullptr) {
            if (!parent) parent = m_rootNode;

            auto obj = gnaNew<T>();
            if constexpr (std::is_base_of_v<grScene::Geometry, T>) {
                m_geometryObjects.push_back(obj);
            } else if constexpr (std::is_base_of_v<grScene::Light, T>) {
                m_lightObjects.push_back(obj);
            }

            parent->addChild(obj);

            return obj;
        }

        void removeObject(gnaPointer<grScene::SceneObject> obj);

        gnaPointer<grScene::Node> m_rootNode;

        std::vector<gnaPointer<grScene::Geometry>> m_geometryObjects;
        std::vector<gnaPointer<grScene::Light>> m_lightObjects;

    protected:
        void postClone() override;

    private:
        void rebuildGeomLightList();
    };

    class GR_SCENE_DLLIMPEXP SceneContainer : public gtlRcObject {
    public:
        GTL_RTTI_DECLARE();

        void addScene(gnaPointer<Scene> scene);

        void update(float deltaTime);
        void postUpdate(float deltaTime);

        std::vector<gnaPointer<Scene>> m_scenes;
    };
}
