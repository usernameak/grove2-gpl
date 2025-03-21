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

#include "nxftGltfImporter.h"

#include <grScene/Scene.h>
#include <grScene/SceneGeom.h>
#include <grScene/SceneEmpty.h>
#include <grScene/Light/SceneLight.h>
#include <nxfIO/FileInputStream.h>

static std::string nxftGltfExpandFilePath(const std::string &path, void *userdata) {
    GTL_NOT_IMPLEMENTED;
}

static bool nxftGltfFileExists(const std::string &path, void *userdata) {
    GTL_NOT_IMPLEMENTED;
}

static bool nxftGltfReadWholeFile(std::vector<unsigned char> *data, std::string *err, const std::string &path, void *userdata) {
    gnaPointer<nxfFileInputStream> fos = gnaNew<nxfFileInputStream>();
    gtl::String gpath(path.c_str(), gtl::String::S_CHARSET_UTF8);
    gnaStatus gerr = fos->open(gpath);
    if (!gerr) {
        *err = "error opening file";
    }
    int64_t size = fos->get_size();
    if (size < 0) {
        *err = "error getting size";
    }
    data->resize(size);
    gnaStatus gnerr = fos->read(data->data(), size, nullptr);
    if (!gnerr) {
        char *cutfErr      = gtl::WCSToUTF8(gnerr.get_errorMessage().toCString());
        std::string utfErr = cutfErr;
        gtl::FreeUTF8(cutfErr);
        *err = utfErr;
        return false;
    }

    return true;
}

static bool nxftGltfWriteWholeFile(std::string *err, const std::string &filepath, const std::vector<unsigned char> &data, void *userdata) {
    assert(false);

    return false;
}

nxftGltfImporter::nxftGltfImporter() {
    m_scene = gnaNew<grScene::Scene>();
}

gnaStatus nxftGltfImporter::importFile(gtl::String path) {
    tinygltf::TinyGLTF loader;
    tinygltf::FsCallbacks fscb{
        .FileExists     = nxftGltfFileExists,
        .ExpandFilePath = nxftGltfExpandFilePath,
        .ReadWholeFile  = nxftGltfReadWholeFile,
        .WriteWholeFile = nxftGltfWriteWholeFile,
    };

    loader.SetFsCallbacks(fscb);
    loader.SetImageLoader(loadImageData, nullptr);

    char *cutfSourcePath      = gtl::WCSToUTF8(path.toCString());
    std::string utfSourcePath = cutfSourcePath;
    gtl::FreeUTF8(cutfSourcePath);

    std::string err;
    std::string warn;
    if (!loader.LoadBinaryFromFile(&model, &err, &warn, utfSourcePath)) {
        return gnaStatus(GNA_E_FAILED, gtl::String(err.c_str()));
    }

    return GNA_E_OK;
}

void nxftGltfImporter::importDefaultScene() {
    return importScene(model.scenes[model.defaultScene]);
}

void nxftGltfImporter::importScene(tinygltf::Scene &scene) {
    m_scene->m_rootNode->name = scene.name.empty() ? GTXT("Scene") : gtl::String(scene.name.c_str(), gtl::String::S_CHARSET_UTF8);

    for (int nodeId : scene.nodes) {
        importNode(m_scene->m_rootNode, model.nodes[nodeId]);
    }
}

gnaPointer<grScene::SceneObject> nxftGltfImporter::importNode(gnaWeakPointer<grScene::Node> parent, tinygltf::Node &inputNode) {
    auto subnode = m_scene->createObject<grScene::Node>(parent);

    gtl::String name = inputNode.name.c_str();
    subnode->name    = name;

    gnaPointer<grScene::SceneObject> outObj = nullptr;
    for (int child : inputNode.children) {
        importNode(subnode, model.nodes[child]);
    }
    if (inputNode.mesh >= 0) {
        importMesh(subnode, model.meshes[inputNode.mesh]);
    }
    if (inputNode.light >= 0) {
        importLight(subnode, model.lights[inputNode.light]);
    }

    // TODO: pull the node up
#if 0
    if (!subnode->firstChild()) {
        outObj = gnaNew<grScene::Empty>();
    } else if (subnode->firstChild() == subnode->lastChild()) {
        outObj = subnode->firstChild();
        subnode->removeSubnode(outObj);
    } else {
        outObj = subnode;
    }
#else
    outObj = subnode;
#endif

    if (inputNode.matrix.size() == 16) {
        assert(false);
    } else {
        if (inputNode.translation.size() == 3) {
            outObj->m_localTransform.translation = {
                (float)inputNode.translation[0],
                (float)inputNode.translation[2],
                (float)inputNode.translation[1]
            };
        }

        if (inputNode.rotation.size() == 4) {
            outObj->m_localTransform.rotation =
                gtlMath2::Quaternionf(
                    -(float)inputNode.rotation[3],
                    -(float)inputNode.rotation[0],
                    (float)inputNode.rotation[2],
                    -(float)inputNode.rotation[1])
                    .toEuler();
        }

        if (inputNode.scale.size() == 3) {
            assert(inputNode.scale[0] == inputNode.scale[1] && inputNode.scale[0] == inputNode.scale[2]);
            outObj->m_localTransform.scale = (float)inputNode.scale[0];
        }
    }

    return outObj;
}

namespace {
    class nxftBufferViewAccessor {
        tinygltf::Model *model;
        tinygltf::Accessor *acc;
        tinygltf::BufferView *bv;
        tinygltf::Buffer *buf;
        int byteStride;
        int byteOffset;

    public:
        nxftBufferViewAccessor(tinygltf::Model *model,
            tinygltf::Accessor *acc) : model(model),
                                       acc(acc) {
            if (model && acc) {
                assert(!acc->sparse.isSparse);

                bv         = &model->bufferViews[acc->bufferView];
                buf        = &model->buffers[bv->buffer];
                byteStride = acc->ByteStride(*bv);
                assert(byteStride >= 0);
                byteOffset = acc->byteOffset + bv->byteOffset;
            }
        }

        gtlMath2::Vector3f readVec3(int position) {
            int bytePosititon      = byteOffset + position * byteStride;
            auto *datap            = buf->data.data();
            gtlMath2::Vector3f pos = *reinterpret_cast<gtlMath2::Vector3f *>(&datap[bytePosititon]);
            return pos;
        }

        gtlMath2::Vector4f readVec4(int position) {
            int bytePosititon      = byteOffset + position * byteStride;
            auto *datap            = buf->data.data();
            gtlMath2::Vector4f pos = *reinterpret_cast<gtlMath2::Vector4f *>(&datap[bytePosititon]);
            return pos;
        }

        gtlMath2::Vector2f readVec2(int position) {
            int bytePosititon = byteOffset + position * byteStride;
            auto *datap       = buf->data.data();
            void *pElem       = &datap[bytePosititon];
            if (acc->componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE && acc->normalized) {
                auto pElems = static_cast<uint8_t *>(pElem);
                return { pElems[0] / (float)UINT8_MAX, pElems[1] / (float)UINT8_MAX };
            } else if (acc->componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT && acc->normalized) {
                auto pElems = static_cast<uint16_t *>(pElem);
                return { pElems[0] / (float)UINT16_MAX, pElems[1] / (float)UINT16_MAX };
            } else if (acc->componentType == TINYGLTF_COMPONENT_TYPE_FLOAT) {
                auto pElems = static_cast<float *>(pElem);
                return { pElems[0], pElems[1] };
            } else {
                assert(false);
                return { 0, 0 };
            }
        }

        uint32_t readUint(int position) {
            int bytePosititon = byteOffset + position * byteStride;
            auto *datap       = buf->data.data();
            void *pElem       = &datap[bytePosititon];
            if (acc->componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE) {
                return *static_cast<uint8_t *>(pElem);
            } else if (acc->componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT) {
                return *static_cast<uint16_t *>(pElem);
            } else if (acc->componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT) {
                return *static_cast<uint32_t *>(pElem);
            } else {
                assert(false);
                return 0;
            }
        }
    };
}

gnaPointer<grScene::Light> nxftGltfImporter::importLight(gnaWeakPointer<grScene::Node> parent, tinygltf::Light &light) {
    gtl::String name = light.name.c_str();

    gnaPointer<grScene::Light> lightObj;
    if (light.type == "directional") {
        auto dirLight = m_scene->createObject<grScene::DirectionalLight>(parent);
        lightObj      = dirLight;

        if (light.color.size() >= 3) {
            dirLight->m_color                   = { (float)light.color[0], (float)light.color[1], (float)light.color[2] };
            dirLight->m_localTransform.rotation = { gtlMath2::pi<float> * 0.5f, 0.0f, 0.0f };
        } else {
            GR_WARNING(GTXT("glTF light color does not have enough members"));
            return nullptr;
        }
    } else {
        GR_WARNING(GTXT("glTF light type `%hs` not supported by importer"), light.type.c_str());
        return nullptr;
    }
    lightObj->name = name;
    return lightObj;
}

gnaPointer<grScene::SceneObject> nxftGltfImporter::importMesh(gnaWeakPointer<grScene::Node> parent, tinygltf::Mesh &mesh) {
    auto snode = m_scene->createObject<grScene::Node>(parent);

    snode->name = gtl::String(mesh.name.c_str(), gtl::String::S_CHARSET_UTF8);

    for (int i = 0; i < mesh.primitives.size(); i++) {
        tinygltf::Primitive &prim = mesh.primitives[i];
        assert(prim.mode == TINYGLTF_MODE_TRIANGLES);

        gnaPointer<grScene::Geometry> geom = m_scene->createObject<grScene::Geometry>(snode);
        geom->name                   = gtl::String::format(GTXT("%ls_Prim%02d"), snode->name.toCString(), i);
        if (prim.material != -1) {
            geom->material = importMaterial(model.materials[prim.material]);
        }

        gnaPointer<grRenderCore::Mesh> gmesh = gnaNew<grRenderCore::Mesh>();
        gmesh->m_primitiveType               = grRenderCore::Mesh::TYPE_TRIANGLES;

        tinygltf::Accessor *posAttr = nullptr;
        tinygltf::Accessor *nrmAttr = nullptr;
        tinygltf::Accessor *tngAttr = nullptr;
        tinygltf::Accessor *uv0Attr = nullptr;
        tinygltf::Accessor *idxAttr = prim.indices < 0 ? nullptr : &model.accessors[prim.indices];

        for (auto &attrib : prim.attributes) {
            if (attrib.first == "POSITION") {
                posAttr = &model.accessors[attrib.second];
            } else if (attrib.first == "NORMAL") {
                nrmAttr = &model.accessors[attrib.second];
            } else if (attrib.first == "TANGENT") {
                tngAttr = &model.accessors[attrib.second];
            } else if (attrib.first == "TEXCOORD_0") {
                uv0Attr = &model.accessors[attrib.second];
            }
        }

        std::underlying_type_t<grRenderCore::VertexFormatFlags> vff = grRenderCore::VFF_POSITION;

        if (nrmAttr) {
            vff |= grRenderCore::VFF_NORMAL;
        }
        if (tngAttr) {
            vff |= grRenderCore::VFF_TANGENT;
        }
        if (uv0Attr) {
            vff |= grRenderCore::VFF_TEXCOORD;
        }

        gmesh->set_vertexFormat(vff);

        nxftBufferViewAccessor posAcc(&model, posAttr);
        nxftBufferViewAccessor nrmAcc(&model, nrmAttr);
        nxftBufferViewAccessor tngAcc(&model, tngAttr);
        nxftBufferViewAccessor uv0Acc(&model, uv0Attr);

        gmesh->set_vertexCount(posAttr->count);

        for (int j = 0; j < posAttr->count; j++) {
            auto v = gmesh->getVertex(j);

            auto pos     = posAcc.readVec3(j);
            v.position() = { pos.x, pos.z, pos.y }; // NOLINT
            if (nrmAttr) {
                auto nrm   = nrmAcc.readVec3(j);
                v.normal() = { nrm.x, nrm.z, nrm.y }; // NOLINT
            }
            if (tngAttr) {
                auto tng    = tngAcc.readVec4(j);
                v.tangent() = { tng.x, tng.z, tng.y, tng.w }; // NOLINT
            }
            if (uv0Attr) {
                auto uv0     = uv0Acc.readVec2(j);
                v.texCoord() = { uv0.x, uv0.y };
            }
        }

        if (idxAttr) {
            nxftBufferViewAccessor idxAcc(&model, idxAttr);
            gmesh->set_indexCount(idxAttr->count);
            for (int j = 0; j < idxAttr->count; j++) {
                gmesh->m_indices[j] = idxAcc.readUint(j);
            }
        }

        gmesh->recomputeBoundingBox();
        gmesh->markDirty();

        geom->set_mesh(gmesh);
    }

    // TODO: merge nodes
#if 0
    if (snode->get_subnodes().size() == 1) {
        gnaPointer<grScene::SceneObject> gnode = snode->get_subnodes()[0];
        gnode->name                     = snode->name;
        gnode->m_localTransform         = snode->m_localTransform;
        snode->removeSubnode(gnode);
        return gnode;
    }
#endif

    return snode;
}

gnaPointer<grScene::MaterialInstance> nxftGltfImporter::importMaterial(tinygltf::Material &mtl) {
    auto gmtl = gnaNew<grScene::MaterialInstance>();
    if (mtl.pbrMetallicRoughness.baseColorTexture.index >= 0) {
        importTexture(
            gmtl, grScene::MaterialInstance::TEXTURE_SLOT_BASECOLOR,
            model.textures[mtl.pbrMetallicRoughness.baseColorTexture.index]);
    }
    if (mtl.normalTexture.index >= 0) {
        importTexture(
            gmtl, grScene::MaterialInstance::TEXTURE_SLOT_NORMALMAP,
            model.textures[mtl.normalTexture.index]);
    }
    return gmtl;
}

void nxftGltfImporter::importTexture(
    gnaWeakPointer<grScene::MaterialInstance> material,
    grScene::MaterialInstance::TextureSlot textureSlot,
    tinygltf::Texture &texture) {

    tinygltf::Image baseColorImage = model.images[texture.source];

    gtl::String strName = gtl::String(baseColorImage.name.c_str(), gtl::String::S_CHARSET_UTF8);
    uint32_t dotIndex   = strName.lastIndexOf(GTXT('.'));
    if (dotIndex != strName.size()) {
        strName = strName.substr(0, dotIndex);
    }

    material->set_texture(
        textureSlot,
        nxfRID{ GTXT("/textures/") + strName }); // TODO: real uri parsing
}


bool nxftGltfImporter::loadImageData(tinygltf::Image *image, const int image_idx, std::string *err,
    std::string *warn, int req_width, int req_height,
    const unsigned char *bytes, int size, void *user_data) {

    image->as_is = true;
    image->image.resize(size);
    std::copy(bytes, bytes + size, image->image.begin());
    return true;
}
