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

#include <gtlMemory/RcObject.h>

namespace grRenderCore {
    class ConstantBufferRenderData : public gtlRcObject {
    public:
        virtual ~ConstantBufferRenderData() = 0;
    };

    inline ConstantBufferRenderData::~ConstantBufferRenderData() = default;

    class ConstantBuffer : public gtlRcObject {
    public:
        bool dirty;

        void markDirty() {
            dirty = true;
        }

        virtual size_t get_data(void **ptr) = 0;

        gnaPointer<ConstantBufferRenderData> m_rendererData;
    };

    template <typename T>
    class ConstantBufferT : public ConstantBuffer {
    public:
        T data;

        size_t get_data(void **ptr) override {
            *ptr = &data;
            return sizeof(T);
        }
    };
}