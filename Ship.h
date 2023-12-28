#pragma once

#include <Windows.h>

#include "Actor.h"
#include "CircleComponent.h"
#include "InputComponent.h"

class Ship : public Actor
{
public:
	Ship(class Game* game);
	~Ship();

	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keyState) override;
private:
	CircleComponent* mCircle;
	InputComponent* mInputComponent;

	float mResetCooldown;
	float mLaserCooldown;
};
