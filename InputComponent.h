#pragma once

#include "MoveComponent.h"

class InputComponent : public MoveComponent
{
public:
	InputComponent(class Actor* owner);

	void ProcessInput(const uint8_t* keyState) override;

	float GetMaxForwardSpeed() const { return mMaxForwardSpeed; }
	float GetMaxAngularSpeed() const { return mMaxAngularSpeed; }
	int GetForwardKey() const { return mForwardKey; }
	int GetBackKey() const { return mBackKey; }
	int GetClockwiseKey() const { return mClockwiseKey; }
	int GetCounterClockwiseKey() const { return mCounterClockwiseKey; }

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