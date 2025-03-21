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

#include "MaterialInstance.h"

#include <nxfResource/Asset/AssetManager.h>

#include <nxfSerialization/NXFFileWriter.h>
#include <nxfSerialization/NXFFileReader.h>
#include <nxfSerialization/PrimitiveSerializers.h>

GTL_RTTI_DEFINE(grScene::MaterialInstance, GTL_RTTI_INHERITS(gtlObject));
NXF_SERIALIZABLE_DEFINE(grScene::MaterialInstance, GR_SCENE_DLLIMPEXP);
GTL_DEFINE_OBJECT_CLONE(grMaterial);

gnaPointer<grScene::MaterialInstance> grScene::MaterialInstance::defaultMaterial;

void grScene::MaterialInstance::set_texture(TextureSlot slot, nxfRID rid) {
    textures[slot]       = rid;
    cachedTextures[slot] = nullptr;
}

const nxfRID &grScene::MaterialInstance::get_textureRID(TextureSlot slot) const {
    return textures[slot];
}

gnaWeakPointer<grImg::Image> grScene::MaterialInstance::get_textureImage(TextureSlot slot) const {
    if (cachedTextures[slot]) {
        return cachedTextures[slot];
    }

    auto &imgRef = cachedTextures[slot];
    gnaSingleton<nxfAssetManager>()->loadOrGetAsset(textures[slot].name, imgRef);
    return imgRef;
}

template <nxfSerialization::SerializationInterface TSerializationInterface>
gnaStatus grScene::MaterialInstance::serializationImpl(TSerializationInterface &proxy) {
    GNA_CHECK_STATUS(gtlObject::serializationImpl(proxy));

    uint32_t numTextureSlots = TEXTURE_SLOT_MAX;
    for (int i = 0; i < numTextureSlots; i++) {
        char str[6];
        snprintf(str, sizeof(str), "tex%d", i);
        GNA_CHECK_STATUS(proxy.serialize(str, textures[i]));
        cachedTextures[i] = nullptr;
    }
    GNA_CHECK_STATUS(proxy.serialize("pipelineName", m_pipelineName));
    GNA_CHECK_STATUS(proxy.serialize("shadowMapPipelineName", m_shadowMapPipelineName));

    return GNA_E_OK;
}

void grScene::MaterialInstance::staticInit() {
    defaultMaterial = gnaNew<grScene::MaterialInstance>();
}

void grScene::MaterialInstance::staticRelease() {
    defaultMaterial = nullptr;
}

void grScene::MaterialInstance::cloneMembers(gnaWeakPointer<gtlCloneable> dest, gtlCloneContext &cctx) const {
    gtlObject::cloneMembers(dest, cctx);

    gnaWeakPointer<grScene::MaterialInstance> cDest = dest.cast<grScene::MaterialInstance>();
    for (uint16_t i = 0; i < TEXTURE_SLOT_MAX; i++) {
        cDest->textures[i] = textures[i];
    }
}
