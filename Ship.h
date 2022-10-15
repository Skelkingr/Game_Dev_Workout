#pragma once

#include "Actor.h"
#include "InputComponent.h"

class Ship : public Actor
{
public:
	enum Direction
	{
		N = 0,
		NW = 1,
		W = 2,
		SW = 3,
		S = 4,
		SE = 5,
		E = 6,
		NE = 7
	};
public:
	Ship(class Game* game);
	
	int GetDirection() const;
	InputComponent* GetInputComponent() const { return mInputComponent; }
private:
	int mDirection;

	InputComponent* mInputComponent;
};
