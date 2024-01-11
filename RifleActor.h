#pragma once

#include "Actor.h"

class RifleActor : public Actor
{
public:
	RifleActor() = delete;
	RifleActor(class Game* game);
	~RifleActor();

	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keys) override;
private:
	class AudioComponent* mAudioComp;
	class MeshComponent* mMeshComp;
};
