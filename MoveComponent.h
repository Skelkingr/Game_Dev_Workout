#pragma once

#include "Component.h"

class MoveComponent : public Component
{
public:
	MoveComponent() = delete;
	MoveComponent(class Actor* owner, int updateOrder = 10);

	void Update(float deltaTime) override;

	float GetAngularSpeed() const { return mAngularSpeed; }
	float GetForwardSpeed() const { return mForwardSpeed; }
	void SetAngularSpeed(float angularSpeed) { mAngularSpeed = angularSpeed; }
	void SetForwardSpeed(float forwardSpeed) { mForwardSpeed = forwardSpeed; }
private:
	float mAngularSpeed;
	float mForwardSpeed;
};