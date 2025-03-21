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
#include <grRenderCore/Mesh/Mesh.h>
#include <grScene/Material/MaterialInstance.h>

namespace grScene {
    class GR_SCENE_DLLIMPEXP Geometry : public grScene::SceneObject {
        gnaPointer<grRenderCore::Mesh> m_mesh;

    public:
        GTL_DECLARE_OBJECT_CLONE;
        GTL_RTTI_DECLARE();
        NXF_SERIALIZABLE_DECLARE();

        gnaPointer<grScene::MaterialInstance> material;

        Geometry();

        template <nxfSerialization::SerializationInterface TSerializationInterface>
        gnaStatus serializationImpl(TSerializationInterface &proxy);

        bool rayCast(const gtlMath2::Ray &ray, grScene::RayCastResult &result) override;

        void updateGlobalBounds() override;

        void set_mesh(gnaPointer<grRenderCore::Mesh> mesh);
        gnaWeakPointer<grRenderCore::Mesh> get_mesh() const {
            return m_mesh;
        }

    protected:
        virtual void initializeMesh() {}
    };
}
