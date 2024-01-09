#pragma once

#include "Actor.h"
#include "SoundEvent.h"

class FPSActor : public Actor
{
public:
	FPSActor() = delete;
	FPSActor(class Game* game);
	~FPSActor();

	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keys) override;

private:
	class AudioComponent* mAudioComp;
	class FPSCamera* mCameraComp;
	class MoveComponent* mMoveComp;

	SoundEvent mFootstep;
	float mLastFootstep;
};

