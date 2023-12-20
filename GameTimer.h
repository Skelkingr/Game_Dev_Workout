#pragma once

#include <SDL.h>

class GameTimer
{
	friend class Game;
	friend class Ship;

public:
	static float GetDeltaTime();	
	static void UpdateTimer();

private:
	static uint32_t mLastTick;
	static uint32_t mCurrentTick;
};

