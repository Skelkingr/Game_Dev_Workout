#pragma once

#include "Actor.h"

#include "Math.h"

class RifleActor : public Actor
{
public:
	RifleActor() = delete;
	RifleActor(class Game* game);
	~RifleActor() = default;

	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keys) override;
private:
	class MeshComponent* mRifleMeshComp;
};
