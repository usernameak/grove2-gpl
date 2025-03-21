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

#include "PipelineEnums.h"

#include <gtlObject/Object.h>
#include <grRenderCore/RenderCoreDLL.h>
#include <gtlString/PooledString.h>
#include <grRenderCore/Mesh/VertexFormat.h>

namespace grRenderCore {
    class GR_RENDERCORE_DLLIMPEXP PipelineObject : public gtlObject {
        gtl::Name m_name;
        std::underlying_type_t<VertexFormatFlags> m_vertexFormat = 0;
        BlendMode m_blendMode  = BLEND_MODE_NORMAL;
        std::unordered_set<gtl::Name> m_keywords;

    public:
        GTL_RTTI_DECLARE();
        GTL_DECLARE_ABSTRACT_OBJECT_CLONE;
        NXF_SERIALIZABLE_DECLARE();

        virtual ~PipelineObject() override = 0;

        void set_name(gtl::Name name) {
            m_name = name;
        }

        gtl::Name get_name() const {
            return m_name;
        }

        void set_vertexFormat(decltype(m_vertexFormat) format) {
            m_vertexFormat = format;
        }

        auto get_vertexFormat() const {
            return m_vertexFormat;
        }

        void set_blendMode(BlendMode blendMode) {
            m_blendMode = blendMode;
        }

        BlendMode get_blendMode() const {
            return m_blendMode;
        }

        void set_keywords(std::unordered_set<gtl::Name> keywords) {
            m_keywords = std::move(keywords);
        }

        [[nodiscard]] const std::unordered_set<gtl::Name> &get_keywords() const {
            return m_keywords;
        }

        template <nxfSerialization::SerializationInterface TSerializationInterface>
        gnaStatus serializationImpl(TSerializationInterface &proxy);
    };
}