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

#include <grScene/Scene.h>
#include <grScene/SceneNode.h>
#include <grScene/Light/SceneLight.h>
#include <grScene/Material/MaterialInstance.h>
#include <thirdparty/tiny_gltf.inc.h>

class nxftGltfImporter {
    tinygltf::Model model;
    gnaPointer<grScene::Scene> m_scene;

public:
    nxftGltfImporter();

    gnaStatus importFile(gtl::String path);

    void importDefaultScene();
    void importScene(tinygltf::Scene &scene);

    gnaWeakPointer<grScene::Scene> getScene() const {
        return m_scene;
    }

private:
    gnaPointer<grScene::SceneObject> importNode(gnaWeakPointer<grScene::Node> parent, tinygltf::Node &inputNode);
    gnaPointer<grScene::Light> importLight(gnaWeakPointer<grScene::Node> parent, tinygltf::Light &light);
    gnaPointer<grScene::SceneObject> importMesh(gnaWeakPointer<grScene::Node> parent, tinygltf::Mesh &mesh);
    gnaPointer<grScene::MaterialInstance> importMaterial(tinygltf::Material &mtl);
    void importTexture(
        gnaWeakPointer<grScene::MaterialInstance> material,
        grScene::MaterialInstance::TextureSlot textureSlot,
        tinygltf::Texture &texture);

    static bool loadImageData(tinygltf::Image *image, const int image_idx, std::string *err,
        std::string *warn, int req_width, int req_height,
        const unsigned char *bytes, int size, void *user_data);
};
