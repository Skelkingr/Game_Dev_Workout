#pragma once

#include "Actor.h"
#include "AnimSpriteComponent.h"*
#include "Game.h"

class Ship : public Actor
{
public:
	Ship(Game* game);

	void UpdateActor(float deltaTime) override;
	void ProcessKeyboard(const uint8_t* state);

	float GetDownSpeed() const { return this->mDownSpeed; }
	float GetRightSpeed() const { return this->mRightSpeed; }
private:
	float mDownSpeed;
	float mRightSpeed;
};
