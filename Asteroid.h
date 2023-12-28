#pragma once

#include "Actor.h"
#include "CircleComponent.h"

class Asteroid : public Actor
{
public:
	Asteroid(class Game* game);
	~Asteroid();

	void UpdateActor(float deltaTime) override;

	CircleComponent* GetCircle() { return mCircle; }
private:
	CircleComponent* mCircle;
};