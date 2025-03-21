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

#include "Engine.h"

#include <gtlUtil/Logging.h>
#include <gtlUtil/Singleton.h>

using namespace grEngine;

Engine::Engine(IEngineApplication *app) : m_app(app) {}

void Engine::engineInit() {
    GR_INFO(GTXT("Engine init..."));

    GR_INFO(GTXT("Engine initialized!"));
}

void Engine::tick(float deltaTimeF) {
    m_app->tick(deltaTimeF);
}

void Engine::shutdown() {
    m_taskQueue.set_policy(gtl::Concurrency::TaskQueue::POLICY_FORCE_TERMINATE);
}

Engine *grEngine::gEngine = nullptr;
