#include "AnimSpriteComponent.h"
#include "Game.h"
#include "InputComponent.h"
#include "Ship.h"

Ship::Ship()
	:
	Actor(nullptr),
	mInputComponent(nullptr)
{}

Ship::Ship(Game* game)
	:
	Actor(game)
{
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);

	std::vector<SDL_Texture*> anims = {
		game->GetTexture("Assets\\Ship01.png"),
		game->GetTexture("Assets\\Ship03.png"),
		game->GetTexture("Assets\\Ship02.png"),
		game->GetTexture("Assets\\Ship04.png")
	};

	asc->SetAnimTextures(anims);

	mInputComponent = new InputComponent(this);

	mInputComponent->SetForwardKey(SDL_SCANCODE_W);
	mInputComponent->SetBackKey(SDL_SCANCODE_S);
	mInputComponent->SetClockwiseKey(SDL_SCANCODE_A);
	mInputComponent->SetCounterClockwiseKey(SDL_SCANCODE_D);

	mInputComponent->SetMaxForwardSpeed(300.0f);
	mInputComponent->SetMaxAngularSpeed(Math::Pi);
}

Ship::~Ship()
{
	delete mInputComponent;
}
