#pragma once

#include "Actor.h"

#include "Math.h"

class RifleActor : public Actor
{
public:
	RifleActor() = delete;
	RifleActor(class Game* game);
	~RifleActor();
private:
	class MeshComponent* mRifleMesh;
};
