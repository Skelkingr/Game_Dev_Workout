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
	bool GetIsExploding() const { return mIsExploding; }

	void Explode();
private:
	AnimSpriteComponent* mAnimSprite;
	CircleComponent* mCircle;
	NavComponent* mNav;

	std::vector<SDL_Texture*> mAnims;

	bool mIsExploding;
};

