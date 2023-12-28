#include "AnimSpriteComponent.h"
#include "Game.h"
#include "InputComponent.h"
#include "Laser.h"
#include "Ship.h"

Ship::Ship(Game* game)
	:
	Actor(game),
	mReset(false),
	mLaserCooldown(0.0f),
	mResetCooldown(0.0f)
{
	mAnimSpriteComponent = new AnimSpriteComponent(this, 150);
	mAnims = {
		GetGame()->GetTexture("Assets/Ship.png")
	};
	mAnimSpriteComponent->SetAnimTextures(mAnims);

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
	delete mAnimSpriteComponent;
	delete mInputComponent;
	delete mCircle;
}

void Ship::UpdateActor(float deltaTime)
{
	mLaserCooldown -= deltaTime;
	mResetCooldown -= deltaTime;

	if (mReset && mResetCooldown <= 0.0f)
	{
		Reset();
	}

	for (auto ast : GetGame()->GetAsteroids())
	{
		if (Intersect(*mCircle, *(ast->GetCircle())) && !mReset)
		{
			Collision();
			break;
		}
	}

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
{
	if (keyState[SDL_SCANCODE_W] && !mReset)
	{
		mAnims.clear();
		mAnims.push_back(GetGame()->GetTexture("Assets/ShipWithThrust.png"));
		mAnimSpriteComponent->SetAnimTextures(mAnims);
	}
	if (!keyState[SDL_SCANCODE_W] && !mReset)
	{
		mAnims.clear();
		mAnims.push_back(GetGame()->GetTexture("Assets/Ship.png"));
		mAnimSpriteComponent->SetAnimTextures(mAnims);
	}

	if (keyState[SDL_SCANCODE_SPACE] && mLaserCooldown <= 0.0f && !mReset)
	{

		Laser* laser = new Laser(GetGame());
		laser->SetPosition(GetPosition());
		laser->SetRotation(GetRotation());

		mLaserCooldown = 0.5f;
	}
}

void Ship::Collision()
{
	mReset = true;
	mResetCooldown = 5.0f;

	mInputComponent->SetMaxForwardSpeed(75.0f);
	mInputComponent->SetMaxAngularSpeed(Math::TwoPi / 4);

	mAnims.clear();
	mAnims.push_back(GetGame()->GetTexture("Assets/Void.png"));
	mAnims.push_back(GetGame()->GetTexture("Assets/Ship.png"));
	mAnimSpriteComponent->SetAnimTextures(mAnims);

	SetPosition(Vector2(512.0f, 384.0f));
	SetRotation(Math::PiOver2);
}

void Ship::Reset()
{
	mReset = false;

	mAnims.pop_back();
	mAnims.push_back(GetGame()->GetTexture("Assets/Ship.png"));

	mInputComponent->SetMaxForwardSpeed(300.0f);
	mInputComponent->SetMaxAngularSpeed(Math::TwoPi);
}

