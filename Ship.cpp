#include "AnimSpriteComponent.h"
#include "Game.h"
#include "InputComponent.h"
#include "Ship.h"

Ship::Ship(Game* game)
	:
	Actor(game)
{
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);

	std::vector<SDL_Texture*> anims = {
		game->GetTexture("Assets/Ship01.png"),
		game->GetTexture("Assets/Ship02.png"),
		game->GetTexture("Assets/Ship03.png"),
		game->GetTexture("Assets/Ship04.png")
	};
	asc->SetAnimTextures(anims);

	InputComponent* ic = new InputComponent(this);
	ic->SetMaxForwardSpeed(150.0f);
	ic->SetMaxAngularSpeed(Math::TwoPi / 2);
}


