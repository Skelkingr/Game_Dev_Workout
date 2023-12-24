#include "Bullet.h"
#include "Enemy.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"

Bullet::Bullet(Game* game)
	:
	Actor(game)
{
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets\\Projectile.png"));

	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(400.0f);

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(5.0f);

	mLiveTime = 1.0f;
}

Bullet::~Bullet()
{
	if (mCircle != nullptr)
	{
		delete mCircle;
		mCircle = nullptr;
	}
}

void Bullet::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	for (Enemy* e : GetGame()->GetEnemies())
	{
		if (Intersect(*mCircle, *(e->GetCircle())))
		{
			e->Explode();
			SetState(EDead);
			GetGame()->PlaySoundFX("Sounds\\Exploding.wav");
			break;
		}
	}

	mLiveTime -= deltaTime;
	if (mLiveTime <= 0.0f)
	{
		SetState(EDead);
	}
}
