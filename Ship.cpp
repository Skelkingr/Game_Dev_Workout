#include "Game.h"
#include "InputComponent.h"
#include "Laser.h"
#include "Ship.h"
#include "SpriteComponent.h"

Ship::Ship(Game* game)
	:
	Actor(game),
	mLaserCooldown(0.0f),
	mResetCooldown(0.0f)
{

	SpriteComponent* sc = new SpriteComponent(this, 150);
	// sc->SetTexture(game->GetTexture("Assets/Ship.png"));

	mInputComponent = new InputComponent(this);
	mInputComponent->SetForwardKey(SDL_SCANCODE_W);
	mInputComponent->SetBackKey(SDL_SCANCODE_S);
	mInputComponent->SetClockwiseKey(SDL_SCANCODE_A);
	mInputComponent->SetCounterClockwiseKey(SDL_SCANCODE_D);
	mInputComponent->SetMaxForwardSpeed(300.0f);
	mInputComponent->SetMaxAngularSpeed(Math::TwoPi);

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(30.0f);
}

Ship::~Ship()
{
	delete mInputComponent;
	delete mCircle;
}

void Ship::UpdateActor(float deltaTime)
{
	mLaserCooldown -= deltaTime;
	mResetCooldown -= deltaTime;

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

void Ship::ActorInput(const uint8_t* keyState)
{}