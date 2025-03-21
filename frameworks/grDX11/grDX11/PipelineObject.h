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

#include "DX11DLL.h"
#include "grRenderCore/Pipeline/PipelineEnums.h"

#include <grRenderCore/Pipeline/PipelineObject.h>

namespace grDX11 {
    class PipelineRenderObject;

    class GR_DX11_DLLIMPEXP PipelineObject : public grRenderCore::PipelineObject {
        // PipelineObject has to be dllexported for development tools

    public:
        enum PrimitiveMode : uint8_t {
            PRIMITIVE_MODE_SOLID,
            PRIMITIVE_MODE_WIREFRAME
        };

        enum CullMode : uint8_t {
            CULL_MODE_NONE,
            CULL_MODE_BACK,
            CULL_MODE_FRONT,
        };

    private:
        gnaPointer<nxfBinaryResource> m_vertexShaderBinary;
        gnaPointer<nxfBinaryResource> m_pixelShaderBinary;
        PipelineRenderObject *m_renderObject = nullptr;
        PrimitiveMode m_primitiveMode        = PRIMITIVE_MODE_SOLID;
        CullMode m_cullMode                  = CULL_MODE_BACK;
        bool m_depthTest                     = true;
        bool m_scissorTest                   = false;

    public:
        GTL_DECLARE_OBJECT_CLONE;
        NXF_SERIALIZABLE_DECLARE();
        GTL_RTTI_DECLARE();

        PipelineObject();
        virtual ~PipelineObject() override;

        void set_vertexShaderBinary(gnaPointer<nxfBinaryResource> resource);
        void set_pixelShaderBinary(gnaPointer<nxfBinaryResource> resource);

        gnaWeakPointer<nxfBinaryResource> get_vertexShaderBinary() const {
            return m_vertexShaderBinary;
        }

        gnaWeakPointer<nxfBinaryResource> get_pixelShaderBinary() const {
            return m_pixelShaderBinary;
        }

        void set_primitiveMode(PrimitiveMode primitiveMode) {
            m_primitiveMode = primitiveMode;
        }

        PrimitiveMode get_primitiveMode() const {
            return m_primitiveMode;
        }

        void set_cullMode(CullMode cullMode) {
            m_cullMode = cullMode;
        }

        CullMode get_cullMode() const {
            return m_cullMode;
        }

        void set_depthTest(bool depthTest) {
            m_depthTest = depthTest;
        }

        bool get_depthTest() const {
            return m_depthTest;
        }

        void set_scissorTest(bool scissorTest) {
            m_scissorTest = scissorTest;
        }

        bool get_scissorTest() const {
            return m_scissorTest;
        }

        void set_renderObject(PipelineRenderObject *renderObject) {
            m_renderObject = renderObject;
        }

        PipelineRenderObject *get_renderObject() const {
            return m_renderObject;
        }

        template <nxfSerialization::SerializationInterface TSerializationInterface>
        gnaStatus serializationImpl(TSerializationInterface &proxy);
    };
}
