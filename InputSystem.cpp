#include "InputSystem.h"

#include <cstring>

#include <SDL/SDL.h>

bool KeyboardState::GetKeyValue(SDL_Scancode keyCode) const
{
	bool result = mCurrState[keyCode] == 1 ? true : false;

	return result;
}

ButtonState KeyboardState::GetKeyState(SDL_Scancode keyCode) const
{
	if (mPrevState[keyCode] == 0)
	{
		if (mCurrState[keyCode] == 0)
		{
			return ENone;
		}
		else
		{
			return EPressed;
		}
	}
	else
	{
		if (mCurrState[keyCode] == 0)
		{
			return EReleased;
		}
		else
		{
			return EHeld;
		}
	}
}

bool InputSystem::Initialize()
{
	mState.Keyboard.mCurrState = SDL_GetKeyboardState(nullptr);
	memset(mState.Keyboard.mPrevState, 0, SDL_NUM_SCANCODES);

	return true;
}

void InputSystem::ShutDown()
{}

void InputSystem::PrepareForUpdate()
{
	memcpy(mState.Keyboard.mPrevState, mState.Keyboard.mCurrState, SDL_NUM_SCANCODES);
}

void InputSystem::Update()
{}
