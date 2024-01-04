#pragma once

#include "Actor.h"
#include "SoundEvent.h"

class SphereActor :	public Actor
{
public:
	SphereActor() = delete;
	SphereActor(class Game* game);
	~SphereActor();

	void UpdateActor(float deltaTime) override;

	void SetDirection();
private:
	class AudioComponent* mAudioComp;
	class MeshComponent* mMeshComp;
	class MoveComponent* mMoveComp;

	SoundEvent mFireLoop;

	int mDirection;
	bool mGoingForward;
};

