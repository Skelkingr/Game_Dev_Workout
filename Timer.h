#pragma once

#include <SDL.h>

class Timer
{
public:
	Timer();

	float GetTotalTime() const;
	float GetDeltaTime() const { return (float)mDeltaTime; }

	void Reset();
	void Start();
	void Stop();
	void Tick();

private:
	double mSecondsPerCount;
	double mDeltaTime;

	uint64_t mBaseTime;
	uint64_t mPausedTime;
	uint64_t mStopTime;
	uint64_t mPrevTime;
	uint64_t mCurrTime;

	bool mStopped;
};

