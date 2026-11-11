#include "../Time.h"
#include <thread>


void Time::Delay(float seconds)
{

    std::this_thread::sleep_for(std::chrono::duration<float>(seconds));
   
}


