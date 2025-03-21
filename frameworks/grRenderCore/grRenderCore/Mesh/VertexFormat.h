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

#include <cstdint>
#include <gtlUtil/Logging.h>
#include <gtlUtil/Misc.h>
#include <gtlString/PooledString.h>

namespace grRenderCore {
    enum VertexFormatAttribute : uint16_t {
        VFA_POSITION           = 0,  // position (+3 floats)
        VFA_TEXCOORD           = 1,  // texture coordinates (+2 floats)
        VFA_NORMAL             = 2,  // normal (+3 floats)
        VFA_COLOR              = 3,  // color (+UBYTE4)
        VFA_TANGENT            = 4,  // tangent + bitangent sign (+4 floats)
        VFA_BLENDINDICES       = 5,  // blend indices (+UBYTE4)
        VFA_BLENDWEIGHTS       = 6,  // blend weights (+4 floats)
        VFA_INSTANCE_TRANSFORM = 16, // instance transform (+3x4 floats)
        VFA_MAX,
        VFA_INVALID = VFA_MAX
    };

    enum VertexFormatFlags : uint32_t {
        VFF_POSITION           = GTL_BIT(VFA_POSITION),           // position (+3 floats)
        VFF_TEXCOORD           = GTL_BIT(VFA_TEXCOORD),           // texture coordinates (+2 floats)
        VFF_NORMAL             = GTL_BIT(VFA_NORMAL),             // normal (+3 floats)
        VFF_COLOR              = GTL_BIT(VFA_COLOR),              // color (+UBYTE4_UNORM)
        VFF_TANGENT            = GTL_BIT(VFA_TANGENT),            // tangent + bitangent sign (+4 floats)
        VFF_BLENDINDICES       = GTL_BIT(VFA_BLENDINDICES),       // blend indices (+UBYTE4)
        VFF_BLENDWEIGHTS       = GTL_BIT(VFA_BLENDWEIGHTS),       // blend weights (+4 floats)
        VFF_INSTANCE_TRANSFORM = GTL_BIT(VFA_INSTANCE_TRANSFORM), // instance transform (+3x4 floats)
    };

    struct VertexFormatInfo {
        uint16_t m_stride;
        uint16_t m_offsets[VFA_MAX];

        VertexFormatInfo() : m_stride{ 0 }, m_offsets{} {}

        explicit VertexFormatInfo(std::underlying_type_t<VertexFormatFlags> vertexFormat) {
            m_stride = 0;
            if (vertexFormat & VFF_POSITION) {
                m_offsets[VFA_POSITION] = m_stride;
                m_stride += sizeof(float) * 3;
            }
            if (vertexFormat & VFF_TEXCOORD) {
                m_offsets[VFA_TEXCOORD] = m_stride;
                m_stride += sizeof(float) * 2;
            }
            if (vertexFormat & VFF_NORMAL) {
                m_offsets[VFA_NORMAL] = m_stride;
                m_stride += sizeof(float) * 3;
            }
            if (vertexFormat & VFF_COLOR) {
                m_offsets[VFA_COLOR] = m_stride;
                m_stride += sizeof(uint8_t) * 4;
            }
            if (vertexFormat & VFF_TANGENT) {
                m_offsets[VFA_TANGENT] = m_stride;
                m_stride += sizeof(float) * 4;
            }
            if (vertexFormat & VFF_BLENDINDICES) {
                m_offsets[VFA_BLENDINDICES] = m_stride;
                m_stride += sizeof(uint8_t) * 4;
            }
            if (vertexFormat & VFF_BLENDWEIGHTS) {
                m_offsets[VFA_BLENDWEIGHTS] = m_stride;
                m_stride += sizeof(float) * 4;
            }
        }
    };

    struct InstanceVertexFormatInfo {
        uint16_t m_stride;
        uint16_t m_offsets[VFA_MAX];

        InstanceVertexFormatInfo() : m_stride{ 0 }, m_offsets{} {}

        explicit InstanceVertexFormatInfo(std::underlying_type_t<VertexFormatFlags> vertexFormat) {
            m_stride = 0;
            if (vertexFormat & VFF_INSTANCE_TRANSFORM) {
                m_offsets[VFA_INSTANCE_TRANSFORM] = m_stride;
                m_stride += sizeof(float) * 3 * 4;
            }
        }
    };

    inline VertexFormatAttribute interpretVFAName(gtl::PooledAString name) {
        static gtl::PooledAString VFS_POSITION("POSITION");
        static gtl::PooledAString VFS_TEXCOORD("TEXCOORD");
        static gtl::PooledAString VFS_NORMAL("NORMAL");
        static gtl::PooledAString VFS_COLOR("COLOR");
        static gtl::PooledAString VFS_TANGENT("TANGENT");
        static gtl::PooledAString VFS_BLENDINDICES("BLENDINDICES");
        static gtl::PooledAString VFS_BLENDWEIGHTS("BLENDWEIGHTS");
        static gtl::PooledAString VFS_INSTANCE_TRANSFORM("INSTANCE_TRANSFORM");

        if (name == VFS_POSITION) {
            return VFA_POSITION;
        } else if (name == VFS_TEXCOORD) {
            return VFA_TEXCOORD;
        } else if (name == VFS_NORMAL) {
            return VFA_NORMAL;
        } else if (name == VFS_COLOR) {
            return VFA_COLOR;
        } else if (name == VFS_TANGENT) {
            return VFA_TANGENT;
        } else if (name == VFS_BLENDINDICES) {
            return VFA_BLENDINDICES;
        } else if (name == VFS_BLENDWEIGHTS) {
            return VFA_BLENDWEIGHTS;
        } else if (name == VFS_INSTANCE_TRANSFORM) {
            return VFA_INSTANCE_TRANSFORM;
        } else {
            return VFA_INVALID; // invalid
        }
    }

    inline gtl::PooledAString toVFAName(VertexFormatAttribute vfa) {
        static gtl::PooledAString VFS_POSITION("POSITION");
        static gtl::PooledAString VFS_TEXCOORD("TEXCOORD");
        static gtl::PooledAString VFS_NORMAL("NORMAL");
        static gtl::PooledAString VFS_COLOR("COLOR");
        static gtl::PooledAString VFS_TANGENT("TANGENT");
        static gtl::PooledAString VFS_BLENDINDICES("BLENDINDICES");
        static gtl::PooledAString VFS_BLENDWEIGHTS("BLENDWEIGHTS");
        static gtl::PooledAString VFS_INSTANCE_TRANSFORM("INSTANCE_TRANSFORM");

        if (vfa == VFA_POSITION) {
            return VFS_POSITION;
        } else if (vfa == VFA_TEXCOORD) {
            return VFS_TEXCOORD;
        } else if (vfa == VFA_NORMAL) {
            return VFS_NORMAL;
        } else if (vfa == VFA_COLOR) {
            return VFS_COLOR;
        } else if (vfa == VFA_TANGENT) {
            return VFS_TANGENT;
        } else if (vfa == VFA_BLENDINDICES) {
            return VFS_BLENDINDICES;
        } else if (vfa == VFA_BLENDWEIGHTS) {
            return VFS_BLENDWEIGHTS;
        } else if (vfa == VFA_INSTANCE_TRANSFORM) {
            return VFS_INSTANCE_TRANSFORM;
        } else {
            GR_FATAL(GTXT("Invalid vertex attribute name"));
        }
    }

    inline std::underlying_type_t<VertexFormatFlags> vertexFormatAttribToFlag(VertexFormatAttribute vfa) {
        return GTL_BIT(vfa);
    }
}