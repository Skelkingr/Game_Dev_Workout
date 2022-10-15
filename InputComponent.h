#pragma once

#include "MoveComponent.h"

class InputComponent : public MoveComponent
{
public:
	InputComponent(class Actor* owner);

	void ProcessInput(const uint8_t* keyState) override;

	float GetMaxForwardSpeed() { return mMaxForwardSpeed; }
	float GetMaxAngularSpeed() { return mMaxAngularSpeed; }
	int GetForwardKey() { return mForwardKey; }
	int GetBackKey() { return mBackKey; }
	int GetClockwiseKey() { return mClockwiseKey; }
	int GetCounterClockwiseKey() { return mCounterClockwiseKey; }

	void SetMaxForwardSpeed(float maxForwardSpeed) { mMaxForwardSpeed = maxForwardSpeed; }
	void SetMaxAngularSpeed(float maxAngularSpeed) { mMaxAngularSpeed = maxAngularSpeed; }
	void SetForwardKey(int forwardKey) { mForwardKey = forwardKey; }
	void SetBackKey(int backKey) { mBackKey = backKey; }
	void SetClockwiseKey(int clockwiseKey) { mClockwiseKey = clockwiseKey; }
	void SetCounterClockwiseKey(int counterClockwiseKey) { mCounterClockwiseKey = counterClockwiseKey; }
private:
	float mMaxForwardSpeed;
	float mMaxAngularSpeed;

	int mForwardKey;
	int mBackKey;

	int mClockwiseKey;
	int mCounterClockwiseKey;
};