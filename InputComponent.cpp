#include "InputComponent.h"

InputComponent::InputComponent(Actor* owner)
	:
	MoveComponent(owner),
	mMaxForwardSpeed(0.0f),
	mMaxAngularSpeed(0.0f),
	mForwardKey(0),
	mBackKey(0),
	mClockwiseKey(0),
	mCounterClockwiseKey(0)
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
		forwardSpeed -= mMaxForwardSpeed;
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