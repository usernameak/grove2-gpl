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

#include <grScene/SceneDLL.h>
#include <grImg/Image.h>

#include <gtlString/PooledString.h>
#include <gtlObject/Object.h>
#include <nxfResource/RID.h>
#include <grColor.h>

namespace grScene {
    class GR_SCENE_DLLIMPEXP MaterialInstance : public gtlObject {
    public:
        enum TextureSlot : uint16_t {
            TEXTURE_SLOT_0 = 0,
            TEXTURE_SLOT_1 = 1,
            TEXTURE_SLOT_2 = 2,
            TEXTURE_SLOT_3 = 3,
            TEXTURE_SLOT_4 = 4,
            TEXTURE_SLOT_5 = 5,
            TEXTURE_SLOT_6 = 6,
            TEXTURE_SLOT_7 = 7,

            TEXTURE_SLOT_MAX,

            TEXTURE_SLOT_BASECOLOR          = TEXTURE_SLOT_0,
            TEXTURE_SLOT_NORMALMAP          = TEXTURE_SLOT_1,
            TEXTURE_SLOT_PBR_MAP            = TEXTURE_SLOT_2,
            TEXTURE_SLOT_TERRAIN_ALPHA_MASK = TEXTURE_SLOT_3,
        };

    private:
        nxfRID textures[TEXTURE_SLOT_MAX];
        mutable gnaPointer<grImg::Image> cachedTextures[TEXTURE_SLOT_MAX];

    public:
        GTL_RTTI_DECLARE();
        GTL_DECLARE_OBJECT_CLONE;
        NXF_SERIALIZABLE_DECLARE();

        static gnaPointer<MaterialInstance> defaultMaterial;

        grColor baseColor{ 0xFFFFFFFF };

        gtl::Name m_pipelineName          = "Lambert_Default";
        gtl::Name m_shadowMapPipelineName = "Shadowmap_Default";

        MaterialInstance() = default;

        MaterialInstance(const nxfRID &baseColorTexture) {
            textures[TEXTURE_SLOT_BASECOLOR] = baseColorTexture;
        }

        void set_texture(TextureSlot slot, nxfRID rid);
        const nxfRID &get_textureRID(TextureSlot slot) const;
        gnaWeakPointer<grImg::Image> get_textureImage(TextureSlot slot) const;

        template <nxfSerialization::SerializationInterface TSerializationInterface>
        gnaStatus serializationImpl(TSerializationInterface &proxy);

        static void staticInit();
        static void staticRelease();
    };
}
