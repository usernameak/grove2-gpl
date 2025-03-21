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

#include <grScene/SceneObject.h>
#include <vector>

namespace grScene {
    class GR_SCENE_DLLIMPEXP Node : public grScene::SceneObject {
        gnaPointer<grScene::SceneObject> m_firstChild;
        gnaWeakPointer<grScene::SceneObject> m_lastChild;

        friend class Scene;

    public:
        GTL_RTTI_DECLARE();
        GTL_DECLARE_OBJECT_CLONE;
        NXF_SERIALIZABLE_DECLARE();

        template <nxfSerialization::SerializationInterface TSerializationInterface>
        gnaStatus serializationImpl(TSerializationInterface &proxy);

        bool rayCast(const gtlMath2::Ray &ray, grScene::RayCastResult &result) override;

        void update(float deltaTime) override;
        void postUpdate(float deltaTime) override;
        void updateGlobalBounds() override;

        gnaWeakPointer<grScene::SceneObject> firstChild() const {
            return m_firstChild;
        }

        gnaWeakPointer<grScene::SceneObject> lastChild() const {
            return m_lastChild;
        }

    private:
        void addChild(gnaWeakPointer<grScene::SceneObject> obj);
        void removeChild(gnaWeakPointer<grScene::SceneObject> obj);
    };
}
