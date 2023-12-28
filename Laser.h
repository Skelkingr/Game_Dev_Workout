#pragma once

#include "Actor.h"
#include "CircleComponent.h"
#include "Game.h"

class Laser : public Actor
{
public:
	Laser(Game* game);

	void UpdateActor(float deltaTime) override;
private:
	CircleComponent* mCircle;
	float mDeathTimer;
};
