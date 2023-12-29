#include "Game.h"
#include "InputComponent.h"
#include "Laser.h"
#include "Ship.h"
#include "SpriteComponent.h"

Ship::Ship(Game* game)
	:
	Actor(game),
	mLaserCooldown(0.0f)
{

	SpriteComponent* sc = new SpriteComponent(this, 150);
	sc->SetTexture(game->GetTexture("Assets/Ship.png"));

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
}

void Ship::ActorInput(const uint8_t* keyState)
{
	if (keyState[SDL_SCANCODE_SPACE] && mLaserCooldown <= 0.0f)
	{
		Laser* laser = new Laser(GetGame());
		laser->SetPosition(GetPosition());
		laser->SetRotation(GetRotation());

		mLaserCooldown = 0.5f;
	}
}