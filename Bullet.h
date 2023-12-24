#pragma once

#include "Actor.h"
#include "CircleComponent.h"
#include "Game.h"

class Bullet : public Actor
{
public:
	Bullet() = delete;
	Bullet(Game* game);
	~Bullet() override;

	void UpdateActor(float deltaTime) override;
private:
	CircleComponent* mCircle;

	float mLiveTime;
};

