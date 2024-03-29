#pragma once

#include "Math.h"

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

class MouseState
{
public:
	friend class InputSystem;

	const Vector2& GetPosition() const { return mMousePos; }
	const Vector2& GetScrollWheel() const { return mScrollWheel; }
	bool IsRelative() const { return mIsRelative; }

	bool GetButtonValue(int button) const;
	ButtonState GetButtonState(int button) const;
private:
	Vector2 mMousePos;
	Vector2 mScrollWheel;

	uint32_t mCurrButtons;
	uint32_t mPrevButtons;

	bool mIsRelative;
};

struct InputState
{
	KeyboardState Keyboard;
	MouseState Mouse;
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
	void ProcessEvent(union SDL_Event& event);

	const InputState& GetState() const { return mState; }

	void SetRelativeMouseMode(bool value);
private:
	InputState mState;
};


