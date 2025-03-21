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

#include <grRenderCore/RenderPass/RenderPass.h>
#include <grRenderCore/ConstantBuffer/ConstantBuffer.h>
#include <grRenderCore/Sampler/Sampler.h>
#include <grRenderCore/Mesh/InstancedMesh.h>

#include <grScene/Scene.h>
#include <grScene/SceneObject.h>
#include <grScene/SceneNode.h>
#include <grScene/Camera.h>
#include <grScene/Light/SceneLight.h>

#include <gtlUtil/Hash.h>

#include <cstdint>

class grScene::MaterialInstance;

namespace grRenderCore {
    class CmdListEmitter;
    class PipelineObject;
}

namespace grRenderView {
    namespace Render {
#pragma pack(push, 4)
        struct SceneUniforms {
            gtlMath2::Matrix4x4f viewProjectionMatrix;
            gtlMath2::Matrix4x4f shadowmapMatrix;
        };

        struct ObjectUniforms {
            gtlMath2::Vector4f materialColor;
        };

        enum LightType : uint32_t {
            LIGHT_TYPE_NONE        = 0,
            LIGHT_TYPE_DIRECTIONAL = 1,
        };

        struct alignas(16) LightUniforms {
            gtlMath2::Vector4f lightColor;
            gtlMath2::Vector4f lightDir;
            LightType type;
        };

        constexpr size_t MAX_LIGHTS = 16;

        struct LightsUniforms {
            LightUniforms lights[MAX_LIGHTS];
        };
#pragma pack(pop)

        struct GeometryRenderInfo {
        };

        class RenderPassShadowView;
        class RenderPassView : public grRenderCore::RenderPass {
            gnaPointer<grRenderCore::ConstantBufferT<SceneUniforms>> m_sceneUniforms;
            gnaPointer<grRenderCore::ConstantBufferT<LightsUniforms>> m_lightsUniforms;
            bool m_enableShadowmapping;
            gnaPointer<grRenderCore::Sampler> m_textureSampler;
            gnaPointer<grRenderCore::Sampler> m_shadowSampler;
            std::unordered_map<gnaPointer<grScene::Light>, RenderPassShadowView> m_shadowMapViews;

        protected:
            gnaPointer<grRenderCore::InstancedMesh> m_instancedMesh;

        public:
            struct InstancingKey {
                gnaWeakPointer<grRenderCore::Mesh> mesh;
                gnaWeakPointer<grScene::MaterialInstance> mtl;

                bool operator==(const InstancingKey &other) const {
                    return mesh == other.mesh && mtl == other.mtl;
                }

                bool operator!=(const InstancingKey &other) const {
                    return !operator==(other);
                }
            };

            struct InstanceInfo {
                std::vector<gnaPointer<grScene::Geometry>> geometries;
                uint32_t startInstance;
                uint32_t numInstances;
            };

            typedef std::unordered_map<InstancingKey, InstanceInfo> InstancedGeometryMap;

            RenderPassView() : RenderPassView(nullptr) {}
            explicit RenderPassView(gnaWeakPointer<grScene::SceneContainer> sceneContainer);

            virtual ~RenderPassView() override;

            void update(float deltaTime) override;
            gnaPointer<grRenderCore::CmdList> prepareCommandList(float deltaTime) override;

            void resize(int width, int height) override;

            void addGeometryToInstanceList(InstancedGeometryMap &map, gnaWeakPointer<grScene::Geometry> geom);
            void prepareInstanceData(InstancedGeometryMap &map);
            void drawGeometry(
                gnaWeakPointer<grRenderCore::CmdListEmitter> cmdList,
                const InstancingKey &instancingKey,
                const InstanceInfo &instanceInfo);

            void set_enableShadowmapping(bool enable);
            bool get_enableShadowmapping() const {
                return m_enableShadowmapping;
            }

            virtual bool bindPipelineFromInstKey(gnaWeakPointer<grRenderCore::CmdListEmitter> cmdList, const InstancingKey &key);
            virtual void setupCameraPerspective();

            gnaPointer<grScene::SceneContainer> m_sceneContainer;
            gnaPointer<grScene::Camera> m_cameraNode;
        };
    }
}

namespace std {
    template <>
    struct hash<grRenderView::Render::RenderPassView::InstancingKey> {
        inline std::size_t operator()(const grRenderView::Render::RenderPassView::InstancingKey &key) const {
            size_t hash = 0;
            gutlHashCombine(hash, key.mesh);
            gutlHashCombine(hash, key.mtl);
            return hash;
        }
    };
}
