#pragma once

#include "Actor.h"
#include "InputComponent.h"

class Ship : public Actor
{
public:
	Ship(class Game* game);
	
	float GetCenterShipX() const { return mCenterShipX; }
	float GetCenterShipY() const { return mCenterShipY; }

private:
	const float mCenterShipX = 480.0f;
	const float mCenterShipY = 369.5f;
};
