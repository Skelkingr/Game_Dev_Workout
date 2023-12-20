#include "GameTimer.h"

uint32_t GameTimer::mLastTick = 0;
uint32_t GameTimer::mCurrentTick = 0;

float GameTimer::GetDeltaTime()
{
    float result = (mCurrentTick - mLastTick) / 1000.0f;
    
    if (result > 0.5f)
        result = 0.5f;
    
    return result;
}

void GameTimer::UpdateTimer()
{
    mLastTick = mCurrentTick;
    mCurrentTick = SDL_GetTicks();
}
