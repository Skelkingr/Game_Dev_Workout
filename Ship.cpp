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
		Reset();

	for (auto ast : GetGame()->GetAsteroids())
	{
		if (Intersect(*mCircle, *(ast->GetCircle())) && !mReset)
		{
			GetGame()->PlaySoundFX("Sounds/CykaBlyat.wav");
			Collision();
			break;
		}
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
		GetGame()->PlaySoundFX("Sounds/LaserShot.wav");

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

	mInputComponent->SetMaxForwardSpeed(37.5f);
	mInputComponent->SetMaxAngularSpeed(Math::TwoPi / 8);

	mAnims.clear();
	mAnims.push_back(GetGame()->GetTexture("Assets/Ship.png"));
	mAnims.push_back(GetGame()->GetTexture("Assets/Void.png"));
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

