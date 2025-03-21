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

#include "RenderStats.h"

#include <chrono>

grRenderCore::RenderStats::RenderStats()
    : fpsNanoCounterLast(0LL),
      intermediateFrames(0),
      fps(0) {
}

void grRenderCore::RenderStats::onFrameStart() {
    intermediateFrames++;

    long long fpsNanoCounter = std::chrono::time_point_cast<std::chrono::nanoseconds>(
        std::chrono::high_resolution_clock::now())
                                   .time_since_epoch()
                                   .count();
    if (fpsNanoCounterLast == 0) {
        fpsNanoCounterLast = fpsNanoCounter;
    }
    if (fpsNanoCounter >= fpsNanoCounterLast + 1000000000L) {
        fpsNanoCounterLast += 1000000000L;
        fps                = intermediateFrames;
        intermediateFrames = 0;
    }
}

unsigned int grRenderCore::RenderStats::get_fps() {
    return fps;
}
