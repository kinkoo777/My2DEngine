#include "core/Time.h"

std::chrono::steady_clock::time_point Time::s_LastFrame;
float Time::s_DeltaTime = 0.0f;
bool Time::s_Initialized = false;

void Time::Update()
{
    auto currentFrame = std::chrono::steady_clock::now();

    if (!s_Initialized)
    {
        s_LastFrame = currentFrame;
        s_Initialized = true;
        return;
    }

    s_DeltaTime =
        std::chrono::duration<float>(
            currentFrame - s_LastFrame
        ).count();

    s_LastFrame = currentFrame;
}

float Time::GetDeltaTime()
{
    return s_DeltaTime;
}