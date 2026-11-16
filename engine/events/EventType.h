#pragma once

enum class EventType
{
    None = 0,

    WindowClose,
    WindowResize,

    KeyPressed,
    KeyReleased,

    MouseMoved,
    MouseButtonPressed,
    MouseButtonReleased
};