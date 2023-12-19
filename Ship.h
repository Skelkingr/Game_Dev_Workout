#pragma once

#include <Windows.h>

#include "Actor.h"
#include "InputComponent.h"
#include "SpriteComponent.h"

class Ship : public Actor
{
public:
	Ship();
	Ship(class Game* game);
	~Ship();

	InputComponent* GetInputComponent() const { return mInputComponent; }

private:
	InputComponent* mInputComponent;
};