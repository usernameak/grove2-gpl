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

#include <functional>
#include <vector>
#include <gtlUtil/Misc.h>
#include <gtlUtil/Logging.h>
#include <cassert>
#include <atomic>

enum class gnaEventPriority : int16_t {
    PRIORITY_HIGHEST   = -500,
    PRIORITY_HIGH      = -100,
    PRIORITY_NORMAL    = 0,
    PRIORITY_LOW       = 100,
    PRIORITY_LOWEST    = 500,
    PRIORITY_MONITOR   = 1000,
    PRIORITY_FINALIZER = INT16_MAX // use *only* if you deallocate the event sink owner on event! special behavior.
};

class gnaEventHandlerHandle {
    template <typename T>
    friend class gnaEventSink;

    std::uintptr_t m_handle;

public:
    gnaEventHandlerHandle() : gnaEventHandlerHandle(nullptr) {}
    gnaEventHandlerHandle(std::nullptr_t handle) : m_handle(0) {}

    /**
     * FOR INTERNAL USE ONLY
     * @param handle handle id
     */
    explicit gnaEventHandlerHandle(std::uintptr_t handle) : m_handle(handle) {}

    operator bool() const {
        return m_handle != 0;
    }

    std::uintptr_t internal_getHandleValue() const {
        return m_handle;
    }
};

class gnaEventSink_InternalSuperclass {
protected:
    static GTL_DLLIMPEXP std::atomic_uintptr_t st_nextHandle;
};

template <typename T>
class gnaEventSink : gnaEventSink_InternalSuperclass {
public:
    typedef std::function<bool(T &)> HandlerFunc;
    typedef std::function<void(T &)> HandlerFuncV;

    enum {
        EVENT_FLAG_EVENT_PENDING_REMOVAL = GTL_BIT(0),
        EVENT_FLAG_HAS_VALID_HANDLE      = GTL_BIT(1),
        EVENT_FLAG_ONE_SHOT              = GTL_BIT(2),
    };

    struct HandlerInfo {
        HandlerFunc func;
        gnaEventPriority priority;
        uint16_t flags;
        void *key;
    };

    std::vector<HandlerInfo> handlers;
    uint32_t pendingEventCounter;

public:
    gnaEventSink() : pendingEventCounter(0) {}

    bool emit(T &ev) {
        ++pendingEventCounter;

        for (auto &handler : handlers) {
            if (handler.flags & EVENT_FLAG_EVENT_PENDING_REMOVAL) continue;

            bool finalizer = false;
            if (handler.priority == gnaEventPriority::PRIORITY_FINALIZER) { // it will be deallocated when it's invoked
                finalizer = true;
            }
            if (handler.flags & EVENT_FLAG_ONE_SHOT) {
                handler.flags |= EVENT_FLAG_EVENT_PENDING_REMOVAL;
            }
            if (!handler.func(ev)) {
                --pendingEventCounter;
                tryRemoveHandlers();

                return false;
            }
            if (finalizer) {
                return true;
            }
        }

        --pendingEventCounter;
        tryRemoveHandlers();

        return true;
    }

    /**
     * Registers an event handler and returns its handle.
     *
     * The event handler should return true if the event needs to
     * be passed onto the next handlers.
     *
     * @param handler the event handler
     * @param priority event priority
     * @param key event key (deprecated, if set, the handle returned won't be valid!)
     */
    gnaEventHandlerHandle addHandler(
        HandlerFunc handler,
        gnaEventPriority priority = gnaEventPriority::PRIORITY_NORMAL,
        void *key                 = nullptr) {

        gnaEventHandlerHandle handle = nullptr;
        addHandlerImpl(handler, priority, key, handle);
        return handle;
    }

    /**
     * Registers an event handler and returns its handle
     *
     * @param handler the event handler
     * @param priority event priority
     * @param key event key (deprecated, if set, the handle returned won't be valid!)
     */
    gnaEventHandlerHandle addHandlerV(HandlerFuncV handler, gnaEventPriority priority = gnaEventPriority::PRIORITY_NORMAL, void *key = nullptr) {
        return addHandler([handler](auto &ev) {
            handler(ev);
            return true;
        },
            priority, key);
    }

    /**
     * Registers an event handler and returns its handle
     *
     * @param handler the event handler
     * @param priority event priority
     * @param key event key (deprecated, if set, the handle returned won't be valid!)
     */
    gnaEventHandlerHandle addHandlerOneShot(HandlerFuncV handler, gnaEventPriority priority = gnaEventPriority::PRIORITY_NORMAL) {
        gnaEventHandlerHandle handle = nullptr;

        HandlerInfo *info = addHandlerImpl([handler](auto &ev) {
            handler(ev);
            return true;
        },
            priority, nullptr, handle);

        info->flags |= EVENT_FLAG_ONE_SHOT;

        return handle;
    }

    /**
     * Removes old key-based handlers
     * @param key handler key specified in addHandler
     */
    [[deprecated]] void removeHandlers(void *key) {
        for (auto it = handlers.begin(); it != handlers.end(); ++it) {
            if (!(it->flags & EVENT_FLAG_HAS_VALID_HANDLE) && it->key == key) {
                it->flags |= EVENT_FLAG_EVENT_PENDING_REMOVAL;
            }
        }
        tryRemoveHandlers();
    }

    /**
     * Removes a handler by its handle
     * @param handle the handle returned from addHandler
     */
    void removeHandler(gnaEventHandlerHandle handle) {
        for (auto it = handlers.begin(); it != handlers.end(); ++it) {
            if ((it->flags & EVENT_FLAG_HAS_VALID_HANDLE) && reinterpret_cast<uintptr_t>(it->key) == handle.m_handle) {
                it->flags |= EVENT_FLAG_EVENT_PENDING_REMOVAL;
            }
        }
        tryRemoveHandlers();
    }

private:
    void tryRemoveHandlers() {
        if (pendingEventCounter) return;

        for (auto it = handlers.begin(); it != handlers.end();) {
            if (it->flags & EVENT_FLAG_EVENT_PENDING_REMOVAL) {
                it = handlers.erase(it);
            } else {
                ++it;
            }
        }
    }


    /**
     * Registers an event handler and returns its handle.
     *
     * The event handler should return true if the event needs to
     * be passed onto the next handlers.
     *
     * @param handler the event handler
     * @param priority event priority
     * @param key event key (deprecated, if set, the handle returned won't be valid!)
     */
    HandlerInfo *addHandlerImpl(
        HandlerFunc handler,
        gnaEventPriority priority,
        void *key,
        gnaEventHandlerHandle &outHandle) {

        for (auto it = handlers.begin();; ++it) {
            if (it == handlers.end() || it->priority > priority) {
                HandlerInfo &info            = *handlers.emplace(it);
                info.priority                = priority;
                info.func                    = handler;
                gnaEventHandlerHandle handle = nullptr;
                if (key != nullptr) {
                    info.flags = 0;
                    info.key   = key;
                } else {
                    uintptr_t uhandle = st_nextHandle.fetch_add(1);
                    if (uhandle == 0) { // let's hope this never happens to anyone.
                        GR_FATAL(GTXT("Exceeded maximum event handler handle amount for %hs"), typeid(T).name());
                    }
                    handle     = static_cast<gnaEventHandlerHandle>(uhandle);
                    info.flags = EVENT_FLAG_HAS_VALID_HANDLE;
                    info.key   = (void *)handle.m_handle;
                }
                outHandle = handle;
                return &info;
            }
        }
    }
};

template <typename Self, typename T, typename A>
static GTL_FORCEINLINE auto gnaEventSink_bindToMemberMethod(Self *self, T (Self::*func)(A)) {
    return [self, func](A arg) { return (self->*func)(arg); };
}

template <typename Self, typename T, typename A>
static GTL_FORCEINLINE auto gnaEventSink_bindToMemberMethod(Self *self, T (Self::*func)(A) const) {
    return [self, func](A arg) { return (self->*func)(arg); };
}

#define GNA_MEMBER_METHOD_EVENT_HANDLER(object, methodName) (gnaEventSink_bindToMemberMethod(&(object), &std::remove_reference_t<decltype(object)>::methodName))
