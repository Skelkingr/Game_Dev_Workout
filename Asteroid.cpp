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
	Vector2 randPos = Random::GetVector(
		Vector2(-static_cast<float>(CLIENT_WIDTH) / 2.0f, -static_cast<float>(CLIENT_HEIGHT) / 2.0f),
		Vector2(static_cast<float>(CLIENT_WIDTH) / 2.0f, static_cast<float>(CLIENT_HEIGHT) / 2.0f)
	);
	SetPosition(randPos);
	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Asteroid.png"));

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
