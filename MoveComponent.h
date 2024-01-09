#pragma once

#include "Component.h"

class MoveComponent : public Component
{
public:
	MoveComponent() = delete;
	MoveComponent(class Actor* owner, int updateOrder = 10);
	~MoveComponent() = default;

	void Update(float deltaTime) override;

	float GetForwardSpeed() const { return mForwardSpeed; }
	float GetStrafeSpeed() const { return mStrafeSpeed; }
	float GetAngularSpeed() const { return mAngularSpeed; }
	
	void SetForwardSpeed(float forwardSpeed) { mForwardSpeed = forwardSpeed; }
	void SetStrafeSpeed(float strafeSpeed) { mStrafeSpeed = strafeSpeed; }
	void SetAngularSpeed(float angularSpeed) { mAngularSpeed = angularSpeed; }
private:
	float mForwardSpeed;
	float mStrafeSpeed;
	float mAngularSpeed;
};