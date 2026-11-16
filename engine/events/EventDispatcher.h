#pragma once

#include "events/Event.h"
#include <utility>

class EventDispatcher
{
public:
    EventDispatcher(Event& event)
        : m_Event(event)
    {
    }

    template<typename T, typename F>
    bool Dispatch(F&& function)
    {
        if (m_Event.GetEventType() == T::GetStaticType())
        {
            std::forward<F>(function)(
                static_cast<T&>(m_Event)
            );

            return true;
        }

        return false;
    }

private:
    Event& m_Event;
};