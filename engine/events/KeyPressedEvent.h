#pragma once

#include "events/Event.h"

class KeyPressedEvent : public Event
{
public:
    KeyPressedEvent(int keyCode, int repeatCount)
        : m_KeyCode(keyCode),
          m_RepeatCount(repeatCount)
    {
    }

    int GetKeyCode() const
    {
        return m_KeyCode;
    }

    int GetRepeatCount() const
    {
        return m_RepeatCount;
    }

    static EventType GetStaticType()
    {
        return EventType::KeyPressed;
    }

    EventType GetEventType() const override
    {
        return GetStaticType();
    }

    const char* GetName() const override
    {
        return "KeyPressed";
    }

    int GetCategoryFlags() const override
    {
        return EventCategory::Input |
               EventCategory::Keyboard;
    }

private:
    int m_KeyCode;
    int m_RepeatCount;
};