#pragma once

#include "Actor.h"

class Ship : public Actor
{
public:
	Ship(class Game* game);

	void UpdateActor(float deltaTime) override;
	void ProcessKeyboard(const uint8_t* state);

	float GetDownSpeed() const { return mDownSpeed; }
	float GetRightSpeed() const { return mRightSpeed; }
private:
	float mDownSpeed;
	float mRightSpeed;
};
