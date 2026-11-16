#pragma once

enum EventCategory
{
    None        = 0,
    App         = 1 << 0,
    Input       = 1 << 1,
    Keyboard    = 1 << 2,
    Mouse       = 1 << 3
};