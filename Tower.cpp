#include "Bullet.h"
#include "Enemy.h"
#include "SpriteComponent.h"
#include "Tower.h"

Tower::Tower(Game* game)
	:
	Actor(game)
{
	SpriteComponent* sc = new SpriteComponent(this, 200);
	sc->SetTexture(game->GetTexture("Assets\\Tower.png"));

	mMove = new MoveComponent(this);

	mNextAttack = mAttacktime;
}

Tower::~Tower()
{
	if (mMove != nullptr)
	{
		delete mMove;
		mMove = nullptr;
	}
}

void Tower::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	mNextAttack -= deltaTime;
	if (mNextAttack <= 0.0f)
	{
		Enemy* e = GetGame()->GetNearestEnemy(GetPosition());
		if (e != nullptr)
		{
			Vector2 dir = e->GetPosition() - GetPosition();
			float dist = dir.Length();
			if (dist < mAttackRange)
			{
				SetRotation(Math::Atan2(-dir.y, dir.x));

				Bullet* b = new Bullet(GetGame());
				b->SetPosition(GetPosition());
				b->SetRotation(GetRotation());
			}
		}

		mNextAttack += mAttacktime;
	}
}
