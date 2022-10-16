#pragma once

#include "Actor.h"
#include "InputComponent.h"

class Ship : public Actor
{
public:
	Ship(class Game* game);
	
	InputComponent* GetInputComponent() const { return mInputComponent; }
private:
	int mDirection;

	InputComponent* mInputComponent;
};
