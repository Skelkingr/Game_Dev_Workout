#include "AnimSpriteComponent.h"
#include "Game.h"
#include "InputComponent.h"
#include "Ship.h"

Ship::Ship(Game* game)
	:
	Actor(game),
	mInputComponent(nullptr)
{
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);

	std::vector<SDL_Texture*> anims = {
		game->GetTexture("Assets/Ship01.png"),
		game->GetTexture("Assets/Ship02.png"),
		game->GetTexture("Assets/Ship03.png"),
		game->GetTexture("Assets/Ship04.png")
	};
	asc->SetAnimTextures(anims);

	mInputComponent = new InputComponent(this);
	mInputComponent->SetMaxForwardSpeed(150.0f);
	mInputComponent->SetMaxAngularSpeed(Math::TwoPi / 4);
}


