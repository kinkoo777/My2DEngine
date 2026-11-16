#pragma once

#include <chrono>

class Time
{
public:
    static void Update();
    static float GetDeltaTime();

private:
    static std::chrono::steady_clock::time_point s_LastFrame;
    static float s_DeltaTime;
    static bool s_Initialized;
};