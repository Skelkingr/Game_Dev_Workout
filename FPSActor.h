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

	void UpdateRifle();
private:
	class AudioComponent* mAudioComp;
	class FPSCamera* mCameraComp;
	class MoveComponent* mMoveComp;
	class RifleActor* mRifle;

	SoundEvent mFootstep;

	float mLastFootstep;
};

