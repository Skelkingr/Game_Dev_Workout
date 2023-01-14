#pragma once

#include "Actor.h"
#include "InputComponent.h"
#include "SpriteComponent.h"

class Ship : public Actor
{
public:
	Ship(class Game* game);
	~Ship();

	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keyState) override;
private:
	SpriteComponent* mSpriteComponent;
	float mLaserCooldown;
};
