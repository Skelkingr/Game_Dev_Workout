#include "Asteroid.h"
#include "Game.h"
#include "Random.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"

Asteroid::Asteroid(Game* game)
	:
	Actor(game),
	mCircle(nullptr)
{
	Vector2 randPos = Random::GetVector(Vector2::Zero, Vector2(1024.0f, 768.0f));
	SetPosition(randPos);
	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

	SpriteComponent* sc = new SpriteComponent(this);
	//sc->SetTexture(game->GetTexture("Assets\\Asteroid.png"));

	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(150.0f);

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(30.0f);

	game->AddAsteroid(this);
}

Asteroid::~Asteroid()
{
	GetGame()->RemoveAsteroid(this);
}

void Asteroid::UpdateActor(float deltaTime)
{
	if (mCircle->GetCenter().y >= 768.0f)
	{
		float positionX = GetPosition().x;
		Vector2 newPosition(positionX, 0.0f);
		SetPosition(newPosition);
		return;
	}

	if (mCircle->GetCenter().x >= 1024.0f)
	{
		float positionY = GetPosition().y;
		Vector2 newPosition(0.0f, positionY);
		SetPosition(newPosition);
		return;
	}

	if (mCircle->GetCenter().y <= 0.0f)
	{
		float positionX = GetPosition().x;
		Vector2 newPosition(positionX, 768.0f);
		SetPosition(newPosition);
		return;
	}

	if (mCircle->GetCenter().x <= 0.0f)
	{
		float positionY = GetPosition().y;
		Vector2 newPosition(1024.0f, positionY);
		SetPosition(newPosition);
		return;
	}
}
