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

#include <deque>
#include <functional>
#include <gtlUtil/Misc.h>

// while this is in gtl::Concurrency, this is not intended as a concurrent task queue and it's not threadsafe.

namespace gtl {
    namespace Concurrency {
        typedef std::function<void(void)> Task;
        class TaskQueue {
            std::deque<Task> m_que;

        public:
            enum Policy {
                POLICY_EXIT_LOOP_ON_EMPTY,
                POLICY_FORCE_TERMINATE,
                POLICY_LOOP
            };

            void enqueue(Task task) {
                m_que.push_back(std::move(task));
            }

            void set_policy(Policy policy) {
                m_policy = policy;
            }

            Policy get_policy() const {
                return m_policy;
            }

            void runLoop() {
                while (m_policy == POLICY_LOOP) {
                    while (m_policy != POLICY_FORCE_TERMINATE && !m_que.empty()) {
                        Task task = std::move(m_que.front());
                        m_que.pop_front();
                        task();
                    }
                }
            }

        private:
            Policy m_policy = POLICY_LOOP;
        };
    }
}