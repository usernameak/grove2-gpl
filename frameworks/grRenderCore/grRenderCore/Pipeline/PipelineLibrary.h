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
#include <gtlUtil/Hash.h>

namespace grRenderCore {
    class PipelineObject;

    struct PipelineKey {
        gtl::Name name;
        std::underlying_type_t<VertexFormatFlags> vertexFormat;
        BlendMode blendMode;
        std::unordered_set<gtl::Name> keywords;

        const bool operator==(const PipelineKey &other) const {
            return name == other.name &&
                   vertexFormat == other.vertexFormat &&
                   blendMode == other.blendMode &&
                   keywords == other.keywords;
        }
    };
}

template <>
struct nxfSerialization::SerializationTraits<grRenderCore::PipelineKey> {
    template <SerializationInterface TSerializationInterface>
    static gnaStatus serialize(const char *name, TSerializationInterface &ser, grRenderCore::PipelineKey &value) {
        GNA_CHECK_STATUS(ser.beginCompound(name));
        GNA_CHECK_STATUS(ser.serialize("name", value.name));
        GNA_CHECK_STATUS(ser.serialize("vertexFormat", value.vertexFormat));
        GNA_CHECK_STATUS(ser.serialize("blendMode", value.blendMode));
        GNA_CHECK_STATUS(ser.serialize("keywords", value.keywords));
        GNA_CHECK_STATUS(ser.endCompound());

        return GNA_E_OK;
    }
};

template <>
struct std::hash<grRenderCore::PipelineKey> {
    std::size_t operator()(const grRenderCore::PipelineKey &pipelineKey) const noexcept {
        std::size_t hash = 0;
        gutlHashCombine(hash, pipelineKey.name);
        gutlHashCombine(hash, pipelineKey.vertexFormat);
        gutlHashCombine(hash, pipelineKey.blendMode);
        size_t kwHash = 0;
        for (const auto &kw : pipelineKey.keywords) {
            kwHash ^= std::hash<gtl::Name>{}(kw);
        }
        gutlHashCombine(hash, kwHash);
        return hash;
    }
};

namespace grRenderCore {
    class GR_RENDERCORE_DLLIMPEXP PipelineLibrary : public gtlObject {
        std::unordered_map<PipelineKey, gnaPointer<PipelineObject>> m_pipelineMap;

    public:
        GTL_RTTI_DECLARE();
        NXF_SERIALIZABLE_DECLARE();

        PipelineLibrary();
        virtual ~PipelineLibrary() override;

        void addPipeline(gnaPointer<PipelineObject> pipeline);

        auto &getPipelines() const {
            return m_pipelineMap;
        }

        gnaWeakPointer<PipelineObject> findPipeline(PipelineKey name) const {
            auto it = m_pipelineMap.find(name);
            if (it == m_pipelineMap.end()) return nullptr;
            return it->second;
        }

        template <nxfSerialization::SerializationInterface TSerializationInterface>
        gnaStatus serializationImpl(TSerializationInterface &proxy);
    };
}
