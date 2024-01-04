#pragma once

enum ButtonState
{
	ENone,
	EPressed,
	EReleased,
	EHeld
};

struct InputState
{

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

