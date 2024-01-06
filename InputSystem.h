#pragma once

#include <SDL/SDL_scancode.h>

enum ButtonState
{
	ENone,
	EPressed,
	EReleased,
	EHeld
};

class KeyboardState
{
public:
	friend class InputSystem;

	bool GetKeyValue(SDL_Scancode keyCode) const;

	ButtonState GetKeyState(SDL_Scancode keyCode) const;
private:
	const uint8_t* mCurrState;
	uint8_t mPrevState[SDL_NUM_SCANCODES];
};

struct InputState
{
	KeyboardState Keyboard;
};

class InputSystem
{
public:
	InputSystem() = default;
	InputSystem(const InputSystem& inputSystem) = delete;
	InputSystem& operator=(const InputSystem& inputSystem) = delete;
	~InputSystem() = default;

	bool Initialize();
	void ShutDown();

	void PrepareForUpdate();
	void Update();

	const InputState& GetState() const { return mState; }
private:
	InputState mState;
};


