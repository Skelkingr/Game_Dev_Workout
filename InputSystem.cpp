#include "InputSystem.h"

#include <SDL/SDL.h>

#include <cstring>

bool KeyboardState::GetKeyValue(SDL_Scancode keyCode) const
{
	return mCurrState[keyCode] == 1;
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

bool MouseState::GetButtonValue(int button) const
{
	return (SDL_BUTTON(button) & mCurrButtons) == 1;
}

ButtonState MouseState::GetButtonState(int button) const
{
	int mask = SDL_BUTTON(button);

	if ((mask & mPrevButtons) == 0)
	{
		if ((mask & mCurrButtons) == 0)
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
		if ((mask & mCurrButtons) == 0)
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

	mState.Mouse.mCurrButtons = 0;
	mState.Mouse.mPrevButtons = 0;

	return true;
}

void InputSystem::ShutDown()
{}

void InputSystem::PrepareForUpdate()
{
	memcpy(mState.Keyboard.mPrevState, mState.Keyboard.mCurrState, SDL_NUM_SCANCODES);

	mState.Mouse.mPrevButtons = mState.Mouse.mCurrButtons;
}

void InputSystem::Update()
{
	int x = 0;
	int y = 0;

	mState.Mouse.mCurrButtons = SDL_GetMouseState(&x, &y);
	mState.Mouse.mMousePos.x = static_cast<float>(x);
	mState.Mouse.mMousePos.y = static_cast<float>(y);
}
