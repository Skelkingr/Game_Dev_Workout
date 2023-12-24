#pragma once

#include "Actor.h"
#include "AnimSpriteComponent.h"
#include "CircleComponent.h"
#include "Game.h"
#include "NavComponent.h"

class Enemy : public Actor
{
public:
	Enemy() = delete;
	Enemy(Game* game);
	~Enemy() override;

	void UpdateActor(float deltaTime) override;

	CircleComponent* GetCircle() { return mCircle; }

	void Explode();
private:
	AnimSpriteComponent* mAnimSprite;
	CircleComponent* mCircle;
	NavComponent* mNav;

	std::vector<SDL_Texture*> mAnims;
};

