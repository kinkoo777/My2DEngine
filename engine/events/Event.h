#pragma once

#include "events/EventType.h"
#include "events/EventCategory.h"

class Event
{
public:
    virtual ~Event() = default;

    virtual EventType GetEventType() const = 0;

    virtual const char* GetName() const = 0;

    virtual int GetCategoryFlags() const = 0;

    bool IsInCategory(EventCategory category) const
    {
        return GetCategoryFlags() & category;
    }
};