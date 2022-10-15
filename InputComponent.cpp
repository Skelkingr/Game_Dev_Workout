#include "InputComponent.h"

#include <SDL.h>

InputComponent::InputComponent(Actor* owner)
	:
	MoveComponent(owner),
	mMaxForwardSpeed(0.0f),
	mMaxAngularSpeed(0.0f),
	mForwardKey(SDL_SCANCODE_W),
	mBackKey(SDL_SCANCODE_S),
	mClockwiseKey(SDL_SCANCODE_A),
	mCounterClockwiseKey(SDL_SCANCODE_D)
{}

void InputComponent::ProcessInput(const uint8_t* keyState)
{
	float forwardSpeed = 0.0f;
	float angularSpeed = 0.0f;

	if (keyState[mForwardKey])
	{
		forwardSpeed += mMaxForwardSpeed;
	}
	if (keyState[mBackKey])
	{
		forwardSpeed -= mMaxForwardSpeed / 2;
	}
	SetForwardSpeed(forwardSpeed);

	if (keyState[mClockwiseKey])
	{
		angularSpeed += mMaxAngularSpeed;
	}
	if (keyState[mCounterClockwiseKey])
	{
		angularSpeed -= mMaxAngularSpeed;
	}
	SetAngularSpeed(angularSpeed);
}
