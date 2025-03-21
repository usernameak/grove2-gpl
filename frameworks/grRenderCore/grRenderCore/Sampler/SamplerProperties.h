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

#include <grRenderCore/RenderTypes.h>
#include <gtlUtil/Hash.h>

namespace grRenderCore {
    // yes, these enums have been copy-pasted from d3d11

    enum SamplingFilter {
        SAMP_FILTER_MIN_MAG_MIP_POINT                          = 0,
        SAMP_FILTER_MIN_MAG_POINT_MIP_LINEAR                   = 0x1,
        SAMP_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT             = 0x4,
        SAMP_FILTER_MIN_POINT_MAG_MIP_LINEAR                   = 0x5,
        SAMP_FILTER_MIN_LINEAR_MAG_MIP_POINT                   = 0x10,
        SAMP_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR            = 0x11,
        SAMP_FILTER_MIN_MAG_LINEAR_MIP_POINT                   = 0x14,
        SAMP_FILTER_MIN_MAG_MIP_LINEAR                         = 0x15,
        SAMP_FILTER_ANISOTROPIC                                = 0x55,
        SAMP_FILTER_COMPARISON_MIN_MAG_MIP_POINT               = 0x80,
        SAMP_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR        = 0x81,
        SAMP_FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT  = 0x84,
        SAMP_FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR        = 0x85,
        SAMP_FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT        = 0x90,
        SAMP_FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR = 0x91,
        SAMP_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT        = 0x94,
        SAMP_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR              = 0x95,
        SAMP_FILTER_COMPARISON_ANISOTROPIC                     = 0xd5,
        SAMP_FILTER_MINIMUM_MIN_MAG_MIP_POINT                  = 0x100,
        SAMP_FILTER_MINIMUM_MIN_MAG_POINT_MIP_LINEAR           = 0x101,
        SAMP_FILTER_MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT     = 0x104,
        SAMP_FILTER_MINIMUM_MIN_POINT_MAG_MIP_LINEAR           = 0x105,
        SAMP_FILTER_MINIMUM_MIN_LINEAR_MAG_MIP_POINT           = 0x110,
        SAMP_FILTER_MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR    = 0x111,
        SAMP_FILTER_MINIMUM_MIN_MAG_LINEAR_MIP_POINT           = 0x114,
        SAMP_FILTER_MINIMUM_MIN_MAG_MIP_LINEAR                 = 0x115,
        SAMP_FILTER_MINIMUM_ANISOTROPIC                        = 0x155,
        SAMP_FILTER_MAXIMUM_MIN_MAG_MIP_POINT                  = 0x180,
        SAMP_FILTER_MAXIMUM_MIN_MAG_POINT_MIP_LINEAR           = 0x181,
        SAMP_FILTER_MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT     = 0x184,
        SAMP_FILTER_MAXIMUM_MIN_POINT_MAG_MIP_LINEAR           = 0x185,
        SAMP_FILTER_MAXIMUM_MIN_LINEAR_MAG_MIP_POINT           = 0x190,
        SAMP_FILTER_MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR    = 0x191,
        SAMP_FILTER_MAXIMUM_MIN_MAG_LINEAR_MIP_POINT           = 0x194,
        SAMP_FILTER_MAXIMUM_MIN_MAG_MIP_LINEAR                 = 0x195,
        SAMP_FILTER_MAXIMUM_ANISOTROPIC                        = 0x1d5
    };

    enum SamplingCmpFunc {
        SAMP_COMPARISON_NEVER         = 1,
        SAMP_COMPARISON_LESS          = 2,
        SAMP_COMPARISON_EQUAL         = 3,
        SAMP_COMPARISON_LESS_EQUAL    = 4,
        SAMP_COMPARISON_GREATER       = 5,
        SAMP_COMPARISON_NOT_EQUAL     = 6,
        SAMP_COMPARISON_GREATER_EQUAL = 7,
        SAMP_COMPARISON_ALWAYS        = 8
    };

    enum SamplingAddressingMode {
        SAMP_ADDRESS_WRAP        = 1,
        SAMP_ADDRESS_MIRROR      = 2,
        SAMP_ADDRESS_CLAMP       = 3,
        SAMP_ADDRESS_BORDER      = 4,
        SAMP_ADDRESS_MIRROR_ONCE = 5
    };

    struct SamplerProperties {
        SamplingFilter filteringMode     = SAMP_FILTER_MIN_MAG_MIP_LINEAR;
        SamplingAddressingMode addrModeU = SAMP_ADDRESS_WRAP;
        SamplingAddressingMode addrModeV = SAMP_ADDRESS_WRAP;
        SamplingAddressingMode addrModeW = SAMP_ADDRESS_WRAP;
        float lodBias                    = 0.0f;
        uint32_t maxAnisotropy           = 1;
        SamplingCmpFunc cmpFunc          = SAMP_COMPARISON_NEVER;
        RGBAColorf borderColor           = { 0.0f, 0.0f, 0.0f, 1.0f };
        float minLOD                     = 0.0f;
        float maxLOD                     = FLT_MAX;

        bool operator==(const SamplerProperties &rhs) const {
            return filteringMode == rhs.filteringMode &&
                   addrModeU == rhs.addrModeU &&
                   addrModeV == rhs.addrModeV &&
                   addrModeW == rhs.addrModeW &&
                   lodBias == rhs.lodBias &&
                   maxAnisotropy == rhs.maxAnisotropy &&
                   cmpFunc == rhs.cmpFunc &&
                   borderColor == rhs.borderColor &&
                   minLOD == rhs.minLOD &&
                   maxLOD == rhs.maxLOD;
        }

        bool operator!=(const SamplerProperties &rhs) const {
            return !(rhs == *this);
        }
    };
}

namespace std {
    template <>
    struct hash<grRenderCore::SamplerProperties> {
        size_t operator()(const grRenderCore::SamplerProperties &props) const {
            size_t hash = 0;
            gutlHashCombine(hash, props.filteringMode);
            gutlHashCombine(hash, props.addrModeU);
            gutlHashCombine(hash, props.addrModeV);
            gutlHashCombine(hash, props.addrModeW);
            gutlHashCombine(hash, props.lodBias);
            gutlHashCombine(hash, props.maxAnisotropy);
            gutlHashCombine(hash, props.cmpFunc);
            gutlHashCombine(hash, props.borderColor.r);
            gutlHashCombine(hash, props.borderColor.g);
            gutlHashCombine(hash, props.borderColor.b);
            gutlHashCombine(hash, props.borderColor.a);
            gutlHashCombine(hash, props.minLOD);
            gutlHashCombine(hash, props.maxLOD);

            return hash;
        }
    };
}
