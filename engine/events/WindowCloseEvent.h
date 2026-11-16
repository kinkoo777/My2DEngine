#pragma once

#include "events/Event.h"

class WindowCloseEvent : public Event
{
public:
    static EventType GetStaticType()
    {
        return EventType::WindowClose;
    }

    EventType GetEventType() const override
    {
        return GetStaticType();
    }

    const char* GetName() const override
    {
        return "WindowClose";
    }

    int GetCategoryFlags() const override
    {
        return EventCategory::App;
    }
};