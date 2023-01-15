#include "Asteroid.h"
#include "Laser.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"

Laser::Laser(Game* game)
	:
	Actor(game),
	mDeathTimer(1.0f)
{
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Laser.png"));

	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(800.0f);

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(5.0f);
}

void Laser::UpdateActor(float deltaTime)
{
	if (
		mCircle->GetCenter().y >= 768.0f
		|| mCircle->GetCenter().x >= 1024.0f
		|| mCircle->GetCenter().y <= 0.0f
		|| mCircle->GetCenter().x <= 0.0f
		)
	{
		SetState(EDead);
	}


	mDeathTimer -= deltaTime;
	if (mDeathTimer <= 0.0f)
	{
		SetState(EDead);
	}
	else
	{
		for (auto ast : GetGame()->GetAsteroids())
		{
			if (Intersect(*mCircle, *(ast->GetCircle())))
			{
				GetGame()->PlaySoundFX("Sounds/Blyat.wav");
 				SetState(EDead);
				ast->SetState(EDead);
				break;
			}
		}
	}
}
