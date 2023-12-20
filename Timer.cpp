#include "Timer.h"

Timer::Timer()
    :
    mSecondsPerCount(0.0),
    mDeltaTime(-1.0),
    mBaseTime(0),
    mPausedTime(0),
    mStopTime(0),
    mPrevTime(0),
    mCurrTime(0),
    mStopped(false)
{}

float Timer::GetTotalTime() const
{
    if (mStopped)
        return (float)((mStopTime - mPausedTime) - mBaseTime) * mSecondsPerCount;

    return (float)((mCurrTime - mPausedTime) - mBaseTime) * mSecondsPerCount;
}

void Timer::Reset()
{
    uint64_t currTime = SDL_GetPerformanceCounter();

    mBaseTime = currTime;
    mPrevTime = currTime;
    mStopTime = 0;
    mStopped = false;
}

void Timer::Start()
{
    uint64_t startTime = SDL_GetPerformanceCounter();

    if (mStopped)
    {
        mPausedTime += (startTime - mStopTime);
        mPrevTime = startTime;
        
        mStopTime = 0;
        mStopped = false;
    }
}

void Timer::Stop()
{
    if (!mStopped)
    {
        uint64_t currTime = SDL_GetPerformanceCounter();

        mStopTime = currTime;
        mStopped = true;
    }
}

void Timer::Tick()
{
    if (mStopped)
    {
        mDeltaTime = 0.0;
        return;
    }

    uint64_t currTime = SDL_GetPerformanceCounter();
    mCurrTime = currTime;

    mDeltaTime = (mCurrTime - mPrevTime) * mSecondsPerCount;

    mPrevTime = mCurrTime;

    if (mDeltaTime < 0.0)
        mDeltaTime = 0.0;
}
