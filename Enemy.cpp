#include "Enemy.h"
#include "Grid.h"
#include "SpriteComponent.h"

#include <algorithm>
#include <iostream>

Enemy::Enemy(Game* game)
	:
	Actor(game)
{
	game->GetEnemies().emplace_back(this);

	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets\\Airplane.png"));

	SetPosition(GetGame()->GetGrid()->GetStartTile()->GetPosition());

	mNav = new NavComponent(this);
	mNav->SetForwardSpeed(150.0f);
	mNav->StartPath(GetGame()->GetGrid()->GetStartTile());

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(25.0f);

	mAnimSprite = new AnimSpriteComponent(this);
	mAnimSprite->SetAnimFPS(mAnimSprite->GetAnimFPS() / 200.0f);
	mAnims = {
		game->GetTexture("Assets\\Explosion\\Explosion_0.png"),
		game->GetTexture("Assets\\Explosion\\Explosion_1.png"),
		game->GetTexture("Assets\\Explosion\\Explosion_2.png"),
		game->GetTexture("Assets\\Explosion\\Explosion_3.png"),
		game->GetTexture("Assets\\Explosion\\Explosion_4.png"),
		game->GetTexture("Assets\\Explosion\\Explosion_5.png"),
		game->GetTexture("Assets\\Explosion\\Explosion_6.png"),
		game->GetTexture("")
	};
}

Enemy::~Enemy()
{
	if (mAnimSprite != nullptr)
	{
		delete mAnimSprite;
		mAnimSprite = nullptr;
	}

	if (mCircle != nullptr)
	{
		delete mCircle;
		mCircle = nullptr;
	}

	if (mNav != nullptr)
	{
		delete mNav;
		mNav = nullptr;
	}

	auto iter = std::find(
		GetGame()->GetEnemies().begin(),
		GetGame()->GetEnemies().end(),
		this
	);

	GetGame()->GetEnemies().erase(iter);
}

void Enemy::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	if (mAnimSprite->GetCurrFrame() == mAnims.size() - 1)
	{
		SetState(EDead);
	}

	Vector2 diff = GetPosition() - GetGame()->GetGrid()->GetEndTile()->GetPosition();
	if (Math::NearZero(diff.Length(), 10.0f))
	{
		SetState(EDead);
	}	
}

void Enemy::Explode()
{
	mNav->SetForwardSpeed(mNav->GetForwardSpeed() / 5.0f);
	mAnimSprite->SetAnimTextures(mAnims);
}
