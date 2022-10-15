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

int Ship::GetDirection() const
{
	// Northwards
	if (GetForward().x == 0 && GetForward().y == 1)
	{
		return Direction::E;
	}

	// Eastwards
	if (GetForward().x == 1 && GetForward().y == 0)
	{
		return Direction::E;
	}
}


