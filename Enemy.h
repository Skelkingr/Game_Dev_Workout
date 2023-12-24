#pragma once

#include "Actor.h"
#include "CircleComponent.h"
#include "Game.h"

class Enemy : public Actor
{
public:
	Enemy() = delete;
	Enemy(Game* game);
	~Enemy() override;

	void UpdateActor(float deltaTime) override;

	CircleComponent* GetCircle() { return mCircle; }
private:
	CircleComponent* mCircle;
};

