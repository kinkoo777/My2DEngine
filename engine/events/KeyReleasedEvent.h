
#pragma once

#include "events/Event.h"

class KeyReleasedEvent : public Event
{
public:
    explicit KeyReleasedEvent(int keyCode)
        : m_KeyCode(keyCode)
    {
    }

    int GetKeyCode() const
    {
        return m_KeyCode;
    }

    static EventType GetStaticType()
    {
        return EventType::KeyReleased;
    }

    EventType GetEventType() const override
    {
        return GetStaticType();
    }

    const char* GetName() const override
    {
        return "KeyReleased";
    }

    int GetCategoryFlags() const override
    {
        return EventCategory::Input |
               EventCategory::Keyboard;
    }

private:
    int m_KeyCode;
};
