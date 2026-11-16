#pragma once

#include "events/Event.h"

class WindowResizeEvent : public Event
{
public:
    WindowResizeEvent(unsigned int width, unsigned int height)
        : m_Width(width),
          m_Height(height)
    {
    }

    unsigned int GetWidth() const
    {
        return m_Width;
    }

    unsigned int GetHeight() const
    {
        return m_Height;
    }

    static EventType GetStaticType()
    {
        return EventType::WindowResize;
    }

    EventType GetEventType() const override
    {
        return GetStaticType();
    }

    const char* GetName() const override
    {
        return "WindowResize";
    }

    int GetCategoryFlags() const override
    {
        return EventCategory::App;
    }

private:
    unsigned int m_Width;
    unsigned int m_Height;
};